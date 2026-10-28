#include "includes.h"

int main(void)
{
	bsp_init();

	check_remote_update();
	check_usart_update();

	return 0;
}



