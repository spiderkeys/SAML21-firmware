/* Auto-generated config file peripheral_gclk_config.h */
#ifndef PERIPHERAL_GCLK_CONFIG_H
#define PERIPHERAL_GCLK_CONFIG_H

	// <<< Use Configuration Wizard in Context Menu >>>

	// <y> Core Clock Source
	// <id> core_gclk_selection

	// <GCLK_PCHCTRL_GEN_GCLK0_Val"> Generic clock generator 0

	// <GCLK_PCHCTRL_GEN_GCLK1_Val"> Generic clock generator 1

	// <GCLK_PCHCTRL_GEN_GCLK2_Val"> Generic clock generator 2

	// <GCLK_PCHCTRL_GEN_GCLK3_Val"> Generic clock generator 3

	// <GCLK_PCHCTRL_GEN_GCLK4_Val"> Generic clock generator 4

	// <GCLK_PCHCTRL_GEN_GCLK5_Val"> Generic clock generator 5

	// <GCLK_PCHCTRL_GEN_GCLK6_Val"> Generic clock generator 6

	// <GCLK_PCHCTRL_GEN_GCLK7_Val"> Generic clock generator 7

	// <i> Select the clock source for CORE.
#ifndef CONF_GCLK_SERCOM3_CORE_SRC
#    define CONF_GCLK_SERCOM3_CORE_SRC GCLK_PCHCTRL_GEN_GCLK0_Val
#endif

	// <y> Slow Clock Source
	// <id> slow_gclk_selection

	// <GCLK_PCHCTRL_GEN_GCLK0_Val"> Generic clock generator 0

	// <GCLK_PCHCTRL_GEN_GCLK1_Val"> Generic clock generator 1

	// <GCLK_PCHCTRL_GEN_GCLK2_Val"> Generic clock generator 2

	// <GCLK_PCHCTRL_GEN_GCLK3_Val"> Generic clock generator 3

	// <GCLK_PCHCTRL_GEN_GCLK4_Val"> Generic clock generator 4

	// <GCLK_PCHCTRL_GEN_GCLK5_Val"> Generic clock generator 5

	// <GCLK_PCHCTRL_GEN_GCLK6_Val"> Generic clock generator 6

	// <GCLK_PCHCTRL_GEN_GCLK7_Val"> Generic clock generator 7

	// <i> Select the slow clock source.
#ifndef CONF_GCLK_SERCOM3_SLOW_SRC
#    define CONF_GCLK_SERCOM3_SLOW_SRC GCLK_PCHCTRL_GEN_GCLK0_Val
#endif

	/**
	 * \def CONF_GCLK_SERCOM3_CORE_FREQUENCY
	 * \brief SERCOM3's Core Clock frequency
	 */
#ifndef CONF_GCLK_SERCOM3_CORE_FREQUENCY
#    define CONF_GCLK_SERCOM3_CORE_FREQUENCY 2000000
#endif

	/**
	 * \def CONF_GCLK_SERCOM3_SLOW_FREQUENCY
	 * \brief SERCOM3's Slow Clock frequency
	 */
#ifndef CONF_GCLK_SERCOM3_SLOW_FREQUENCY
#    define CONF_GCLK_SERCOM3_SLOW_FREQUENCY 2000000
#endif

	// <y> TC Clock Source
	// <id> tc_gclk_selection

	// <GCLK_PCHCTRL_GEN_GCLK0_Val"> Generic clock generator 0

	// <GCLK_PCHCTRL_GEN_GCLK1_Val"> Generic clock generator 1

	// <GCLK_PCHCTRL_GEN_GCLK2_Val"> Generic clock generator 2

	// <GCLK_PCHCTRL_GEN_GCLK3_Val"> Generic clock generator 3

	// <GCLK_PCHCTRL_GEN_GCLK4_Val"> Generic clock generator 4

	// <GCLK_PCHCTRL_GEN_GCLK5_Val"> Generic clock generator 5

	// <GCLK_PCHCTRL_GEN_GCLK6_Val"> Generic clock generator 6

	// <GCLK_PCHCTRL_GEN_GCLK7_Val"> Generic clock generator 7

	// <i> Select the clock source for TC.
#ifndef CONF_GCLK_TC0_SRC
#    define CONF_GCLK_TC0_SRC GCLK_PCHCTRL_GEN_GCLK0_Val
#endif

	/**
	 * \def CONF_GCLK_TC0_FREQUENCY
	 * \brief TC0's Clock frequency
	 */
#ifndef CONF_GCLK_TC0_FREQUENCY
#    define CONF_GCLK_TC0_FREQUENCY 2000000
#endif

	// <y> ADC Clock Source
	// <id> adc_gclk_selection

	// <GCLK_PCHCTRL_GEN_GCLK0_Val"> Generic clock generator 0

	// <GCLK_PCHCTRL_GEN_GCLK1_Val"> Generic clock generator 1

	// <GCLK_PCHCTRL_GEN_GCLK2_Val"> Generic clock generator 2

	// <GCLK_PCHCTRL_GEN_GCLK3_Val"> Generic clock generator 3

	// <GCLK_PCHCTRL_GEN_GCLK4_Val"> Generic clock generator 4

	// <GCLK_PCHCTRL_GEN_GCLK5_Val"> Generic clock generator 5

	// <GCLK_PCHCTRL_GEN_GCLK6_Val"> Generic clock generator 6

	// <GCLK_PCHCTRL_GEN_GCLK7_Val"> Generic clock generator 7

	// <i> Select the clock source for ADC.
#ifndef CONF_GCLK_ADC_SRC
#    define CONF_GCLK_ADC_SRC GCLK_PCHCTRL_GEN_GCLK0_Val
#endif

	/**
	 * \def CONF_GCLK_ADC_FREQUENCY
	 * \brief ADC's Clock frequency
	 */
#ifndef CONF_GCLK_ADC_FREQUENCY
#    define CONF_GCLK_ADC_FREQUENCY 2000000
#endif

	/**
	 * \def CONF_CPU_FREQUENCY
	 * \brief CPU's Clock frequency
	 */
#ifndef CONF_CPU_FREQUENCY
#    define CONF_CPU_FREQUENCY 2000000
#endif

	// <<< end of configuration section >>>

#endif         // PERIPHERAL_GCLK_CONFIG_H