#!/usr/bin/env python3
"""
Forge - Build & Release Tool for Autoconf Projects
Single-file Python tool with TUI (Textual)
"""

import sys
import os
import shutil
import logging
import subprocess
import platform
from pathlib import Path
import toml

from textual.app import App, ComposeResult
from textual.widgets import Button, Header, Footer, Log
from textual.containers import Vertical
from textual import events

# -------------------------
# Logging setup
# -------------------------
log = logging.getLogger("forge")
logging.basicConfig(
    level=logging.DEBUG,
    format="%(asctime)s [%(levelname)s] forge: %(message)s"
)

# -------------------------
# Detect platform
# -------------------------
PY_PLATFORM = platform.system().lower()
if PY_PLATFORM.startswith("mingw") or PY_PLATFORM.startswith("windows"):
    CURRENT_PLATFORM = "windows"
elif PY_PLATFORM.startswith("linux"):
    CURRENT_PLATFORM = "linux"
elif PY_PLATFORM.startswith("darwin"):
    CURRENT_PLATFORM = "macos"
else:
    CURRENT_PLATFORM = "linux"

# -------------------------
# Helper functions
# -------------------------
def run(cmd, cwd=None):
    """Run a command and raise if it fails, logging output"""
    log.debug("Running command: %s", " ".join(cmd))
    result = subprocess.run(cmd, cwd=cwd, text=True, capture_output=True)
    log.debug(result.stdout)
    log.debug(result.stderr)
    result.check_returncode()
    return result

def write_log(widget: Log, message: str):
    """Write to TUI log and Python logging"""
    widget.write(message)
    log.info(message)

def clean_build(root: Path, build_dir: Path, widget: Log):
    """Remove platform-specific build folder"""
    if build_dir.exists():
        shutil.rmtree(build_dir)
        write_log(widget, f"Removed build folder: {build_dir}")

def clean_autoconf(root: Path, widget: Log):
    """Remove bootstrap/autoconf files"""
    files_to_remove = [
        "configure", "Makefile.in", "aclocal.m4",
        "autom4te.cache"
    ]
    for f in files_to_remove:
        path = root / f
        if path.exists():
            if path.is_dir():
                shutil.rmtree(path)
            else:
                path.unlink()
            write_log(widget, f"Removed {path}")

def bootstrap_autoconf(root: Path, widget: Log):
    """Run autoconf bootstrap if configure missing"""
    configure_path = root / "configure"
    if configure_path.exists():
        write_log(widget, "Configure script exists, skipping bootstrap")
        return
    write_log(widget, "Bootstrapping Autoconf project...")
    try:
        run(["autoreconf", "-i"], cwd=root)
        write_log(widget, "Bootstrap complete")
    except subprocess.CalledProcessError as e:
        write_log(widget, f"Bootstrap failed: {e}")
        raise

def build_project(root: Path, config: dict, widget: Log, platform_name: str):
    """Run configure + make in platform-specific folder"""
    platform_cfg = config["platforms"].get(platform_name, {})
    build_subdir = platform_cfg.get("build_subdir", platform_name)
    build_dir = root / config["build"]["build_dir"] / build_subdir
    build_dir.mkdir(parents=True, exist_ok=True)

    # Run configure
    configure_flags = platform_cfg.get("configure_flags", [])
    configure_script = root / "configure"
    if not configure_script.exists():
        bootstrap_autoconf(root, widget)

    write_log(widget, f"Running configure in {build_dir}...")
    run([str(configure_script), *configure_flags], cwd=build_dir)
    write_log(widget, "Configure complete")

    # Run make
    jobs = config["build"].get("jobs", 1)
    write_log(widget, f"Running make -j{jobs} in {build_dir}...")
    run(["make", f"-j{jobs}"], cwd=build_dir)
    write_log(widget, "Build complete")

def github_release(root: Path, config: dict, widget: Log):
    """Create GitHub release (requires gh CLI)"""
    repo = config["release"]["github_repo"]
    artifacts_glob = config["release"].get("artifacts", ["build/*"])
    write_log(widget, f"Creating GitHub release for {repo}...")
    try:
        # Example: tag with version from project config
        version = config["project"]["version"]
        run(["gh", "release", "create", f"v{version}", *artifacts_glob], cwd=root)
        write_log(widget, "Release complete")
    except subprocess.CalledProcessError as e:
        write_log(widget, f"Release failed: {e}")
        raise

# -------------------------
# Forge App TUI
# -------------------------
class ForgeApp(App):

    CSS_PATH = None
    BINDINGS = [("q", "quit", "Quit")]

    def __init__(self, root: Path, config: dict):
        super().__init__()
        App.title = "Forge - Build & Release Tool"
        self.root = root
        self.config = config

    def compose(self) -> ComposeResult:
        yield Header()
        yield Vertical(
            Button("Bootstrap Autoconf", id="bootstrap"),
            Button("Build", id="build"),
            Button("Build + Release", id="release"),
            Button("Clean Build", id="clean_build"),
            Button("Clean All", id="clean_all"),
            Button("Exit", id="exit"),
            Log(id="log"),
        )
        yield Footer()

    def on_button_pressed(self, event: Button.Pressed) -> None:
        log_widget = self.query_one("#log", Log)
        try:
            if event.button.id == "bootstrap":
                bootstrap_autoconf(self.root, log_widget)

            elif event.button.id == "build":
                build_project(self.root, self.config, log_widget, CURRENT_PLATFORM)

            elif event.button.id == "release":
                build_project(self.root, self.config, log_widget, CURRENT_PLATFORM)
                github_release(self.root, self.config, log_widget)

            elif event.button.id == "clean_build":
                platform_cfg = self.config["platforms"].get(CURRENT_PLATFORM, {})
                build_subdir = platform_cfg.get("build_subdir", CURRENT_PLATFORM)
                build_dir = self.root / self.config["build"]["build_dir"] / build_subdir
                clean_build(self.root, build_dir, log_widget)

            elif event.button.id == "clean_all":
                # clean build and autoconf files
                platform_cfg = self.config["platforms"].get(CURRENT_PLATFORM, {})
                build_subdir = platform_cfg.get("build_subdir", CURRENT_PLATFORM)
                build_dir = self.root / self.config["build"]["build_dir"] / build_subdir
                clean_build(self.root, build_dir, log_widget)
                clean_autoconf(self.root, log_widget)

            elif event.button.id == "exit":
                self.exit()

        except subprocess.CalledProcessError as e:
            write_log(log_widget, f"ERROR: {e}")
            log.exception("Operation failed")

# -------------------------
# Main
# -------------------------
def main():
    root = Path(__file__).parent.parent.parent.resolve()
    config_path = root / "forge.toml"

    if not config_path.exists():
        print(f"Missing forge.toml at {config_path}")
        sys.exit(1)

    config = toml.load(config_path)
    print(f"Forge starting. Project root: {root}")
    app = ForgeApp(root, config)
    app.run()

if __name__ == "__main__":
    main()
