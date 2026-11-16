using UnrealBuildTool;

public class AreaTools : ModuleRules
{
    public AreaTools(ReadOnlyTargetRules Target) : base(Target)
    {
        CppStandard = CppStandardVersion.Cpp20;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        bLegacyPublicIncludePaths = false;

        PublicDependencyModuleNames.AddRange(new[] {
            "Core", "CoreUObject", "Engine", "InputCore", "UMG", "Slate", "SlateCore",
            "HTTP", "Json", "Projects", "FactoryGame", "SML"
        });
    }
}
