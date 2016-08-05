#include <core.h>
#include <hri/hri_nvmctrl.h>


void SysInit()
{
	// Since we are operating at 4MHz, we can leave the wait states at 0
	hri_nvmctrl_set_CTRLB_RWS_bf( NVMCTRL, 0 );
	
	// _osc32kctrl_init_sources();
	// _oscctrl_init_sources();
	// _mclk_init();
	// _gclk_init_generators();
	// _oscctrl_init_referenced_generators();
}

int main()
{
	// Chip and peripheral initialization
	SysInit();

	Setup();

	// Program loop
	while(1)
	{
		Loop();
	}
}
