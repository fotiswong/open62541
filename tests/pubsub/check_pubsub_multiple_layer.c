/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright (c) 2017 - 2018 Fraunhofer IOSB (Author: Andreas Ebner)
 */

#include "ua_server_pubsub.h"
#include "src_generated/ua_types_generated_encoding_binary.h"
#include "ua_types.h"
#include "ua_pubsub.h"
#include "ua_config_default.h"
#include "ua_network_pubsub_udp.h"
#include "ua_server_internal.h"
#include "check.h"
#include "stdio.h"

UA_Server *server = NULL;
UA_ServerConfig *config = NULL;
UA_NodeId connection1, connection2;

static void setup(void) {
}

static void teardown(void) {
}

START_TEST(AddMultipleTransportLayers){
    config = UA_ServerConfig_new_default();

    UA_PubSubTransportLayer pubsubTransportLayer;

    ck_assert_int_eq(config->pubsubTransportLayersSize, 0);

    pubsubTransportLayer = UA_PubSubTransportLayerUDPMP();
    UA_ServerConfig_addPubSubTransportLayer(config, &pubsubTransportLayer);
    ck_assert_int_eq(config->pubsubTransportLayersSize, 1);

    pubsubTransportLayer = UA_PubSubTransportLayerUDPMP();
    UA_ServerConfig_addPubSubTransportLayer(config, &pubsubTransportLayer);
    ck_assert_int_eq(config->pubsubTransportLayersSize, 2);

    pubsubTransportLayer = UA_PubSubTransportLayerUDPMP();
    UA_ServerConfig_addPubSubTransportLayer(config, &pubsubTransportLayer);
    ck_assert_int_eq(config->pubsubTransportLayersSize, 3);

    server = UA_Server_new(config);
    UA_Server_delete(server);

    UA_ServerConfig_delete(config);

    } END_TEST


int main(void) {
    TCase *tc_add_pubsub_writergroup = tcase_create("PubSub Layer allocation");
    tcase_add_checked_fixture(tc_add_pubsub_writergroup, setup, teardown);
    tcase_add_test(tc_add_pubsub_writergroup, AddMultipleTransportLayers);

    Suite *s = suite_create("PubSub Multiple layer handling");
    suite_add_tcase(s, tc_add_pubsub_writergroup);

    SRunner *sr = srunner_create(s);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr,CK_NORMAL);
    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
