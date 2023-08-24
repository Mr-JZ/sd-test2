#include "ip4/test_ip4.h"
#include "../../../lwip/src/include/lwip/init.h"
#include "../../../lwip/test/unit/api/test_sockets.h"
#include "../../../lwip/test/unit/core/test_def.h"
#include "../../../lwip/test/unit/core/test_mem.h"
#include "../../../lwip/test/unit/core/test_netif.h"
#include "../../../lwip/test/unit/core/test_pbuf.h"
#include "../../../lwip/test/unit/core/test_timers.h"
#include "../../../lwip/test/unit/dhcp/test_dhcp.h"
#include "../../../lwip/test/unit/etharp/test_etharp.h"
#include "../../../lwip/test/unit/ip4/test_ip4.h"
#include "../../../lwip/test/unit/ip6/test_ip6.h"
#include "../../../lwip/test/unit/lwip_check.h"
#include "../../../lwip/test/unit/mdns/test_mdns.h"
#include "../../../lwip/test/unit/mqtt/test_mqtt.h"
#include "../../../lwip/test/unit/tcp/test_tcp.h"
#include "../../../lwip/test/unit/tcp/test_tcp_oos.h"
#include "../../../lwip/test/unit/udp/test_udp.h"
#if !NO_SYS
#include "lwip/tcpip.h"
#endif

Suite* create_suite(const char* name, testfunc *tests, size_t num_tests, SFun setup, SFun teardown)
{
  size_t i;
  Suite *s = suite_create(name);

  for(i = 0; i < num_tests; i++) {
    TCase *tc_core = tcase_create(name);
    if ((setup != NULL) || (teardown != NULL)) {
      tcase_add_checked_fixture(tc_core, setup, teardown);
    }
    tcase_add_named_test(tc_core, tests[i]);
    suite_add_tcase(s, tc_core);
  }
  return s;
}

void lwip_check_ensure_no_alloc(unsigned int skip)
{
  int i;
  unsigned int mask;

  if (!(skip & SKIP_HEAP)) {
    fail_unless(lwip_stats.mem.used == 0);
  }
  for (i = 0, mask = 1; i < MEMP_MAX; i++, mask <<= 1) {
    if (!(skip & mask)) {
      fail_unless(lwip_stats.memp[i]->used == 0);
    }
  }
}

#ifdef LWIP_UNITTESTS_LIB
int lwip_unittests_run(void)
#else
int main(void)
#endif
{
  int number_failed;
  SRunner *sr;
  size_t i;
  suite_getter_fn* suites[] = {
    ip4_suite,
    ip6_suite,
    udp_suite,
    tcp_suite,
    tcp_oos_suite,
    def_suite,
    mem_suite,
    netif_suite,
    pbuf_suite,
    timers_suite,
    etharp_suite,
    dhcp_suite,
    mdns_suite,
    mqtt_suite,
    sockets_suite
  };
  size_t num = sizeof(suites)/sizeof(void*);
  LWIP_ASSERT("No suites defined", num > 0);

#if NO_SYS
  lwip_init();
#else
  tcpip_init(NULL, NULL);
#endif

  sr = srunner_create((suites[0])());
  srunner_set_xml(sr, "lwip_unittests.xml");
  for(i = 1; i < num; i++) {
    srunner_add_suite(sr, ((suite_getter_fn*)suites[i])());
  }

#ifdef LWIP_UNITTESTS_NOFORK
  srunner_set_fork_status(sr, CK_NOFORK);
#endif
#ifdef LWIP_UNITTESTS_FORK
  srunner_set_fork_status(sr, CK_FORK);
#endif

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
