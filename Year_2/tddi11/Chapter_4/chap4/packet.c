#include <os_cpu.h>
#include <os_cfg.h>
#include <ucos_ii.h> /* os_c??.h must be included before ! */
#include <libepc.h>

#include "inbound.h"
#include "elapsed.h"
#include "serial.h"

static OS_EVENT *semaphore = NULL;

void ReceivePackets(void)
{
	SerialInit();

	for (;;)
	{
		int type, byte, bytes;
		BYTE8 *bfr;

		if (SerialGet() != 0xFF)
			continue;

		switch (type = SerialGet())
		{
		default:
			continue;
		case 1:
		case 2:
			break;
		}

		bytes = SerialGet();
		bfr = (BYTE8 *)malloc(bytes);
		if (!bfr)
		{
			for (;;)
				;
		}

		for (byte = 0; byte < bytes; byte++)
		{
			bfr[byte] = SerialGet();
		}
		switch (type)
		{
		case 1:
			PostText(bfr);
			break;
		case 2:
			PostTime(bfr);
			break;
		}
	}
}


void SendPacket(int type, BYTE8 *bfr, int bytes)
{

	BYTE8 *err = NULL;

	if (semaphore == NULL)
		semaphore = OSSemCreate(1);
		
	OSSemPend(semaphore, 0, err);


	SerialPut(0xFF);
	//OSTimeDly(10);
	SerialPut(type);
	//OSTimeDly(10);	
	SerialPut(bytes);
	//OSTimeDly(10);
	
	for (int i = 0; i < bytes; i++)
		SerialPut(bfr[i]);

	OSSemPost(semaphore);

	/*
	 * Your code here !
	 */
}
