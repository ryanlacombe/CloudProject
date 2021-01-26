#include "Engine.h"
//#include "ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(ComputeShaders, All, All);

class FComputeShaders : public IModuleInterface
{
	public:
	
	virtual void StartupModule() override;
	
	virtual void ShutdownModule() override;
};