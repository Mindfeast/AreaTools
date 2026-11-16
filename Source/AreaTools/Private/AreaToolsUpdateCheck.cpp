#include "AreaToolsUpdateCheck.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Interfaces/IPluginManager.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

DEFINE_LOG_CATEGORY_STATIC(LogAreaToolsUpdate, Log, All);

static const TCHAR* LatestReleaseUrl = TEXT("https://api.github.com/repos/Mindfeast/AreaTools/releases/latest");

void FAreaToolsUpdateCheck::Run()
{
	TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin(TEXT("AreaTools"));
	if (!Plugin) return;
	const FString Current = Plugin->GetDescriptor().VersionName;

	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Req = FHttpModule::Get().CreateRequest();
	Req->SetURL(LatestReleaseUrl);
	Req->SetVerb(TEXT("GET"));
	Req->SetHeader(TEXT("Accept"), TEXT("application/vnd.github+json"));
	Req->SetHeader(TEXT("User-Agent"), TEXT("AreaTools-UpdateCheck"));
	Req->OnProcessRequestComplete().BindLambda([Current](FHttpRequestPtr, FHttpResponsePtr Resp, bool bOk)
	{
		if (!bOk || !Resp || Resp->GetResponseCode() != 200) return;
		TSharedPtr<FJsonObject> Json;
		if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Resp->GetContentAsString()), Json) || !Json) return;
		FString Tag = Json->GetStringField(TEXT("tag_name"));
		Tag.RemoveFromStart(TEXT("v"));
		FString Url = Json->GetStringField(TEXT("html_url"));
		if (Tag != Current)
		{
			UE_LOG(LogAreaToolsUpdate, Warning, TEXT("AreaTools %s available (installed %s): %s"), *Tag, *Current, *Url);
		}
	});
	Req->ProcessRequest();
}
