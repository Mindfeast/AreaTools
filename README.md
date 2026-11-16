# AreaTools

Satisfactory mod (SML plugin, C++). Select an area, then act on everything inside it.

## Status: 0.1.0 scaffold, never compiled yet

| Feature | State |
|---|---|
| Polygon + min/max height selection (`FATAreaSelection`) | code written |
| Mass dismantle with refund (`UATMassDismantle`) | code written, needs a compile pass against the FactoryGame headers |
| In-game "new version" log notice | code written |
| Equipment, right-click menu, corner and plane markers, eyedropper | TODO, needs Unreal Editor assets (item descriptor, recipe, widget) |
| Copy-paste, fill, set recipe, clear inventories | planned |

## Auto-update

- `watch-satisfactory.yml` runs every 6 hours. It reads the latest SML release (game version, engine) and compares with `compat.json`. On a change it bumps `compat.json` and the `.uplugin`, opens a PR and triggers `build.yml`.
- `build.yml` packages the mod on a **self-hosted Windows runner** (labels `self-hosted, windows, satisfactory`) and publishes a GitHub release on `v*` tags. GitHub-hosted runners cannot build: the CSS Unreal Engine fork is private.
- A game update that breaks the FactoryGame API still needs a manual code fix in the PR.
- In game, the mod logs a warning when a newer release exists. Install updates through the Satisfactory Mod Manager.

## Dev setup

1. Follow the Starter Project guide at https://docs.ficsit.app to get UE `5.6.1-CSS`, Wwise and the SML checkout.
2. `$env:SML_PROJECT = "<SML checkout>"; $env:UE_ROOT = "<engine>"; ./scripts/build.ps1`
3. Register a runner with labels `self-hosted,windows,satisfactory` on that machine.
