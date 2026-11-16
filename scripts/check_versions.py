#!/usr/bin/env python3
"""Compare compat.json with the latest SML release.
Prints key=value lines (changed, sml, gameVersion, engine) for GitHub Actions.
With --write, also updates compat.json and AreaTools.uplugin."""
import json, os, re, sys, urllib.request


def get(url):
    req = urllib.request.Request(url, headers={"User-Agent": "AreaTools-updater"})
    tok = os.environ.get("GH_TOKEN")
    if tok:
        req.add_header("Authorization", f"Bearer {tok}")
    return urllib.request.urlopen(req, timeout=30).read().decode()


root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
compat_path = os.path.join(root, "compat.json")
compat = json.load(open(compat_path))

sml = json.loads(get("https://api.github.com/repos/satisfactorymodding/SatisfactoryModLoader/releases/latest"))["tag_name"].lstrip("v")
base = "https://raw.githubusercontent.com/satisfactorymodding/SatisfactoryModLoader/v%s/" % sml
uplugin = json.loads(get(base + "Mods/SML/SML.uplugin"))
uproject = json.loads(get(base + "FactoryGame.uproject"))

new = {"sml": sml, "gameVersion": uplugin["GameVersion"], "engine": uproject["EngineAssociation"]}
changed = any(compat.get(k) != v for k, v in new.items())
print("changed=" + ("true" if changed else "false"))
for k, v in new.items():
    print(f"{k}={v}")

if "--write" in sys.argv and changed:
    compat.update(new)
    compat["lastVerifiedBuild"] = None
    json.dump(compat, open(compat_path, "w"), indent=2)
    p = os.path.join(root, "AreaTools.uplugin")
    t = open(p, encoding="utf-8").read()
    t = re.sub(r'"GameVersion":\s*"[^"]*"', '"GameVersion": "%s"' % new["gameVersion"], t)
    t = re.sub(r'("Name": "SML", "SemVersion": )"[^"]*"', r'\1"^%s"' % sml, t)
    open(p, "w", encoding="utf-8").write(t)
