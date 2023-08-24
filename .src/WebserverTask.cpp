/*
 * ReglerTask.cpp
 *
 * Created on 18.07.2023
 * 		Author: Meese
 */

#include <cstdlib>

#include "FreeRTOS.h"
#include "PeriodicTaskBase.h"
#include "../template/stm32facade.h"

#include "WebserverTask.h"

// Statische IP-Adresse fuer den Nucleo L476RG
#define IP_ADDR0 192
#define IP_ADDR1 168
#define IP_ADDR2 0
#define IP_ADDR3 100

using namespace Platform::BSP;

WebserverTask::WebserverTask(const char *const name, uint16_t stackDepth,
		osPriority priority, bool immidiateStart) :
		PeriodicTaskBase(name, stackDepth, priority, 10, immidiateStart) {

}

void WebserverTask::m_task() {

	// LwIP initialisieren
	lwip_init();

	// IP-Adresse setzen
	struct ip_addr ipaddr;
	IP4_ADDR(&ipaddr, IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);

	// Netmask und Gateway setzen (optional)
	struct ip_addr netmask, gw;
	IP4_ADDR(&netmask, 255, 255, 255, 0);
	IP4_ADDR(&gw, IP_ADDR0, IP_ADDR1, IP_ADDR2, 1);

	// Netzwerkschnittstelle hinzufuegen (ETH-Interface fuer Nucleo L476RG)
	netif_add(&netif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init,
			&ethernet_input);

	// Netzwerkschnittstelle aktivieren
	netif_set_default (&netif);
	netif_set_up(&netif);

	// TCP-Socket erstellen
	struct tcp_pcb *pcb = tcp_new();
	tcp_bind(pcb, IP_ADDR_ANY, 80);
	pcb = tcp_listen(pcb);

	// Callback-Funktion für eingehende Verbindungen registrieren
	tcp_accept(pcb, http_server_callback);

	while (1) {
		// LwIP-Aufgaben bearbeiten
		sys_check_timeouts();
	}

}

err_t WebserverTask::http_server_callback(void *arg, struct tcp_pcb *tpcb,
		struct pbuf *p, err_t err) {
	if (p != NULL) {
		// Ressourcendaten (z. B. HTML-Seite) hier vorbereiten
		const char *response_data =
				"<html><body><h1>Hello, World!</h1></body></html>";
		int response_length = strlen(response_data);

		// HTTP-Antwort-Header senden
		char header[128];
		snprintf(header, sizeof(header),
				"HTTP/1.1 200 OK\r\nContent-Length: %d\r\n\r\n",
				response_length);
		tcp_write(tpcb, header, strlen(header), TCP_WRITE_FLAG_COPY);

		// Ressourcendaten senden
		tcp_write(tpcb, response_data, response_length, TCP_WRITE_FLAG_COPY);

		// Verbindung schließen
		tcp_close(tpcb);

		// Puffer freigeben
		pbuf_free(p);
	}

	return ERR_OK;
}

