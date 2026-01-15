#!/usr/bin/env python3

import subprocess
import platform
import logging
import sys
from pathlib import Path

# -------------------------
# Logging setup
# -------------------------

LOG_FILE = "forge.log"

logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s [%(levelname)s] %(name)s: %(message)s",
    handlers=[
        logging.FileHandler(LOG_FILE, encoding="utf-8"),
        logging.StreamHandler(sys.stdout),
    ],
)

write_log = logging.getLogger("forge")

# -------------------------
# Imports with dependencies
# -------------------------

try:
    import tomllib  # py3.11+
except ImportError:
    write_log.error("Python 3.11+ required (tomllib missing)")
    sys.exit(1)




try:
    from textual.app import App, ComposeResult
    from textual.widgets import Button, Header, Footer, Log
    from textual.containers import Vertical
except ImportError:
    print(
        "Your Textual version is too old.\n\n"
        "Debian ships an outdated Textual package.\n"
        "Please use a virtual environment:\n\n"
        "  python3 -m venv .venv\n"
        "  source .venv/bin/activate\n"
        "  pip install 'textual>=0.50'\n"
    )
    raise

# -------------------------
# Utilities
# -------------------------

def run(cmd, cwd=None):
    write_log.debug("Running command: %s", " ".join(cmd))
    subprocess.run(cmd, cwd=cwd, check=True)

def find_project_root() -> Path:
    here = Path(__file__).resolve()
    for parent in here.parents:
        if (parent / "forge.toml").exists():
            write_log.info("Project root found at %s", parent)
            return parent
    raise RuntimeError("forge.toml not found (project root unresolved)")

# -------------------------
# Config
# -------------------------

def load_config(root: Path) -> dict:
    cfg = root / "forge.toml"
    write_log.info("Loading config: %s", cfg)
    with cfg.open("rb") as f:
        return tomllib.load(f)

# -------------------------
# Autoconf bootstrap
# -------------------------

def bootstrap_autoconf(root: Path):
    write_log.info("Bootstrapping Autoconf")
    run(["autoreconf", "-fi"], cwd=root)

# -------------------------
# Build system
# -------------------------

def detect_platform():
    sysname = platform.system().lower()
    if "windows" in sysname:
        return "windows"
    if "linux" in sysname:
        return "linux"
    if "darwin" in sysname:
        return "macos"
    return sysname

def build_project(root: Path, config: dict):
    build_cfg = config.get("build", {})
    build_dir = root / build_cfg.get("build_dir", "build")
    jobs = build_cfg.get("jobs", 1)

    target = detect_platform()
    platform_cfg = config.get("platforms", {}).get(target, {})
    flags = platform_cfg.get("configure_flags", [])

    build_dir.mkdir(exist_ok=True)

    write_log.info("Building for platform: %s", target)
    write_log.debug("Configure flags: %s", flags)

    run([str(root / "configure"), *flags], cwd=build_dir)
    run(["make", f"-j{jobs}"], cwd=build_dir)

# -------------------------
# GitHub Release
# -------------------------

def github_release(root: Path, config: dict):
    project = config["project"]
    release = config["release"]

    tag = f"v{project['version']}"
    name = f"{project['name']} {project['version']}"

    write_log.info("Creating GitHub release %s", tag)

    run([
        "gh", "release", "create", tag,
        "--repo", release["github_repo"],
        "--title", name,
        "--generate-notes"
    ])

    artifacts = release.get("artifacts", [])
    if artifacts:
        run(["gh", "release", "upload", tag, *artifacts])

# -------------------------
# TUI
# -------------------------

class ForgeApp(App):
    CSS = "Vertical { padding: 1; }"

    def __init__(self, root: Path, config: dict):
        super().__init__()
        self.root = root
        self.config = config

    def compose(self) -> ComposeResult:
        yield Header()
        yield Vertical(
            Button("Bootstrap Autoconf", id="bootstrap"),
            Button("Build", id="build"),
            Button("Build + Release", id="release"),
            Button("Exit", id="exit"),
            Log(id="write_log"),
        )
        yield Footer()

    def write_log(self, message: str):
        self.query_one("#write_log", Log).write(message)
        write_log.info(message)

    def on_button_pressed(self, event: Button.Pressed):
        try:
            if event.button.id == "bootstrap":
                self.write_log("Bootstrapping Autoconf…")
                bootstrap_autoconf(self.root)
                self.write_log("Bootstrap done")

            elif event.button.id == "build":
                self.write_log("Building project…")
                build_project(self.root, self.config)
                self.write_log("Build done")

            elif event.button.id == "release":
                self.write_log("Building project…")
                build_project(self.root, self.config)
                self.write_log("Creating GitHub release…")
                github_release(self.root, self.config)
                self.write_log("Release done")

            elif event.button.id == "exit":
                self.exit()

        except Exception as e:
            self.write_log(f"ERROR: {e}")
            write_log.exception("Operation failed")

# -------------------------
# Main
# -------------------------

def main():
    root = find_project_root()
    config = load_config(root)

    write_log.info("Forge starting")
    app = ForgeApp(root, config)
    app.run()

if __name__ == "__main__":
    main()
