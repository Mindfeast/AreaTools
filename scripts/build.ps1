# Packages AreaTools with the SML starter project.
# Env: SML_PROJECT = SatisfactoryModLoader checkout (has FactoryGame.uproject)
#      UE_ROOT     = UE 5.6.1-CSS engine folder
param(
  [string]$SmlProject = $env:SML_PROJECT,
  [string]$UeRoot = $env:UE_ROOT
)
$ErrorActionPreference = "Stop"
if (-not $SmlProject -or -not $UeRoot) { throw "Set SML_PROJECT and UE_ROOT" }
$repo = Split-Path -Parent $PSScriptRoot
$link = Join-Path $SmlProject "Mods/AreaTools"
if (-not (Test-Path $link)) { New-Item -ItemType Junction -Path $link -Target $repo | Out-Null }
& "$UeRoot/Engine/Build/BatchFiles/RunUAT.bat" -ScriptsForProject="$SmlProject/FactoryGame.uproject" `
  PackagePlugin -Project="$SmlProject/FactoryGame.uproject" -dlcname=AreaTools -merge -utf8output `
  -clientconfig=Shipping -serverconfig=Shipping -platform=Win64 -nocompileeditor -installed
if ($LASTEXITCODE -ne 0) { throw "Packaging failed" }
$ver = (Get-Content "$repo/AreaTools.uplugin" -Raw | ConvertFrom-Json).VersionName
New-Item -ItemType Directory -Force "$repo/dist" | Out-Null
Compress-Archive -Path "$SmlProject/Saved/ArchivedPlugins/AreaTools/*" -DestinationPath "$repo/dist/AreaTools-$ver.zip" -Force
