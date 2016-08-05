#include <core.h>
#include <peripherals/nvmctrl.hpp>


void SysInit()
{
	//PNvmctrl::set_CTRLB_RWS_bf( 2 );
	
	// _osc32kctrl_init_sources();
	// _oscctrl_init_sources();
	// _mclk_init();
	// _gclk_init_generators();
	// _oscctrl_init_referenced_generators();
}

int main()
{
	// Chip and peripheral initialization
	// system_init();	

	Setup();

	// Program loop
	while(1)
	{
		Loop();
	}
}
