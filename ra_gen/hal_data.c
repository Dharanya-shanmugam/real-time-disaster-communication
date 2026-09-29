/* generated HAL source file - do not edit */
#include "hal_data.h"
rmac_instance_ctrl_t g_ether0_ctrl;
static rmac_buffer_node_t g_ether0_buffer_node_list[24];

uint8_t g_ether0_mac_address[6] =
{ 0x00, 0x11, 0x22, 0x33, 0x44, 0x55 };
layer3_switch_target_port_bitmaps_t g_ether0_target_port_bitmap =
{ .ports =
{ RMAC_LINK_PORT_BITMASK_PORT1 | 0U, }, };

layer3_switch_ts_reception_process_descriptor_t g_ether0_ts_descriptor_array0[8];
rmac_queue_info_t g_ether0_ts_queue[1] =
{
{ .queue_cfg =
{ .array_length = 8, .p_descriptor_array = NULL, .p_ts_descriptor_array = g_ether0_ts_descriptor_array0, .ports = (1
        << 1),
  .type = LAYER3_SWITCH_QUEUE_TYPE_TX, .write_back_mode = LAYER3_SWITCH_WRITE_BACK_MODE_FULL, .descriptor_format =
          LAYER3_SWITCH_DISCRIPTOR_FORMTAT_TX_TIMESTAMP,
  .rx_timestamp_storage = LAYER3_SWITCH_RX_TIMESTAMP_STORAGE_DISABLE, } }, };
layer3_switch_descriptor_t g_ether0_tx_descriptor_array0[3 + 1];
layer3_switch_descriptor_t g_ether0_tx_descriptor_array1[3 + 1];
rmac_queue_info_t g_ether0_tx_queue_list[2] =
{
{ .queue_cfg =
{ .array_length = 3 + 1, .p_descriptor_array = g_ether0_tx_descriptor_array0, .p_ts_descriptor_array = NULL, .ports = (1
        << 1),
  .type = LAYER3_SWITCH_QUEUE_TYPE_TX, .write_back_mode = LAYER3_SWITCH_WRITE_BACK_MODE_FULL, .descriptor_format =
          LAYER3_SWITCH_DISCRIPTOR_FORMTAT_EXTENDED,
  .rx_timestamp_storage = LAYER3_SWITCH_RX_TIMESTAMP_STORAGE_DISABLE, } },
  { .queue_cfg =
  { .array_length = 3 + 1, .p_descriptor_array = g_ether0_tx_descriptor_array1, .p_ts_descriptor_array = NULL, .ports =
            (1 << 1),
    .type = LAYER3_SWITCH_QUEUE_TYPE_TX, .write_back_mode = LAYER3_SWITCH_WRITE_BACK_MODE_FULL, .descriptor_format =
            LAYER3_SWITCH_DISCRIPTOR_FORMTAT_EXTENDED,
    .rx_timestamp_storage = LAYER3_SWITCH_RX_TIMESTAMP_STORAGE_DISABLE, } }, };
layer3_switch_descriptor_t g_ether0_rx_descriptor_array0[3 + 1];
layer3_switch_descriptor_t g_ether0_rx_descriptor_array1[3 + 1];
rmac_queue_info_t g_ether0_rx_queue_list[2] =
{
{ .queue_cfg =
{ .array_length = 3 + 1, .p_descriptor_array = g_ether0_rx_descriptor_array0, .p_ts_descriptor_array = NULL, .ports = (1
        << 1) | (0x0),
  .type = LAYER3_SWITCH_QUEUE_TYPE_RX, .write_back_mode = LAYER3_SWITCH_WRITE_BACK_MODE_FULL, .descriptor_format =
          LAYER3_SWITCH_DISCRIPTOR_FORMTAT_EXTENDED,
#if LAYER3_SWITCH_CFG_GPTP_ENABLE
.rx_timestamp_storage = LAYER3_SWITCH_RX_TIMESTAMP_STORAGE_ENABLE,
#else
  .rx_timestamp_storage = LAYER3_SWITCH_RX_TIMESTAMP_STORAGE_DISABLE,
#endif
        } },
  { .queue_cfg =
  { .array_length = 3 + 1, .p_descriptor_array = g_ether0_rx_descriptor_array1, .p_ts_descriptor_array = NULL, .ports =
            (1 << 1) | (0x0),
    .type = LAYER3_SWITCH_QUEUE_TYPE_RX, .write_back_mode = LAYER3_SWITCH_WRITE_BACK_MODE_FULL, .descriptor_format =
            LAYER3_SWITCH_DISCRIPTOR_FORMTAT_EXTENDED,
#if LAYER3_SWITCH_CFG_GPTP_ENABLE
.rx_timestamp_storage = LAYER3_SWITCH_RX_TIMESTAMP_STORAGE_ENABLE,
#else
    .rx_timestamp_storage = LAYER3_SWITCH_RX_TIMESTAMP_STORAGE_DISABLE,
#endif
          } }, };

const rmac_extended_cfg_t g_ether0_extended_cfg_t =
{ .p_ether_switch = &g_layer3_switch0, .tx_queue_num = 2, .rx_queue_num = 2,

.p_ts_queue = g_ether0_ts_queue,
  .p_tx_queue_list = g_ether0_tx_queue_list, .p_rx_queue_list = g_ether0_rx_queue_list,
#if defined(VECTOR_NUMBER_ETHER_RMPI1)
                .rmpi_irq                = VECTOR_NUMBER_ETHER_RMPI1,
#else
  .rmpi_irq = FSP_INVALID_VECTOR,
#endif
  .rmpi_ipl = (BSP_IRQ_DISABLED),
  .p_buffer_node_list = g_ether0_buffer_node_list, .buffer_node_num = 24, .transmission_descriptor_format =
          RMAC_TRANSMISSION_DESCRIPTOR_FORMAT_DIRECT,
  .p_link_monitored_ports = &g_ether0_target_port_bitmap, .link_detection = RMAC_LINK_DETECTION_DEFAULT_PORTS_UP, };
uint8_t g_ether0_ether_buffer0[1536];
uint8_t g_ether0_ether_buffer1[1536];
uint8_t g_ether0_ether_buffer2[1536];
uint8_t g_ether0_ether_buffer3[1536];
uint8_t g_ether0_ether_buffer4[1536];
uint8_t g_ether0_ether_buffer5[1536];
uint8_t g_ether0_ether_buffer6[1536];
uint8_t g_ether0_ether_buffer7[1536];
uint8_t g_ether0_ether_buffer8[1536];
uint8_t g_ether0_ether_buffer9[1536];
uint8_t g_ether0_ether_buffer10[1536];
uint8_t g_ether0_ether_buffer11[1536];
uint8_t g_ether0_ether_buffer12[1536];
uint8_t g_ether0_ether_buffer13[1536];
uint8_t g_ether0_ether_buffer14[1536];
uint8_t g_ether0_ether_buffer15[1536];
uint8_t g_ether0_ether_buffer16[1536];
uint8_t g_ether0_ether_buffer17[1536];
uint8_t g_ether0_ether_buffer18[1536];
uint8_t g_ether0_ether_buffer19[1536];
uint8_t g_ether0_ether_buffer20[1536];
uint8_t g_ether0_ether_buffer21[1536];
uint8_t g_ether0_ether_buffer22[1536];
uint8_t g_ether0_ether_buffer23[1536];

uint8_t *pp_g_ether0_ether_buffers[24] =
{ (uint8_t*) &g_ether0_ether_buffer0[0],
  (uint8_t*) &g_ether0_ether_buffer1[0],
  (uint8_t*) &g_ether0_ether_buffer2[0],
  (uint8_t*) &g_ether0_ether_buffer3[0],
  (uint8_t*) &g_ether0_ether_buffer4[0],
  (uint8_t*) &g_ether0_ether_buffer5[0],
  (uint8_t*) &g_ether0_ether_buffer6[0],
  (uint8_t*) &g_ether0_ether_buffer7[0],
  (uint8_t*) &g_ether0_ether_buffer8[0],
  (uint8_t*) &g_ether0_ether_buffer9[0],
  (uint8_t*) &g_ether0_ether_buffer10[0],
  (uint8_t*) &g_ether0_ether_buffer11[0],
  (uint8_t*) &g_ether0_ether_buffer12[0],
  (uint8_t*) &g_ether0_ether_buffer13[0],
  (uint8_t*) &g_ether0_ether_buffer14[0],
  (uint8_t*) &g_ether0_ether_buffer15[0],
  (uint8_t*) &g_ether0_ether_buffer16[0],
  (uint8_t*) &g_ether0_ether_buffer17[0],
  (uint8_t*) &g_ether0_ether_buffer18[0],
  (uint8_t*) &g_ether0_ether_buffer19[0],
  (uint8_t*) &g_ether0_ether_buffer20[0],
  (uint8_t*) &g_ether0_ether_buffer21[0],
  (uint8_t*) &g_ether0_ether_buffer22[0],
  (uint8_t*) &g_ether0_ether_buffer23[0], };
const ether_cfg_t g_ether0_cfg =
{ .channel = 1, .zerocopy = ETHER_ZEROCOPY_DISABLE, .multicast = ETHER_MULTICAST_ENABLE, .promiscuous =
          ETHER_PROMISCUOUS_DISABLE,
  .flow_control = ETHER_FLOW_CONTROL_DISABLE, .padding = ETHER_PADDING_DISABLE, .padding_offset = 0, .broadcast_filter =
          0,
  .p_mac_address = g_ether0_mac_address,

  .num_tx_descriptors = 12,
  .num_rx_descriptors = 12,

  .pp_ether_buffers = pp_g_ether0_ether_buffers,

  .ether_buffer_size = 1536,

  .irq = FSP_INVALID_VECTOR,

  .p_callback = NULL,
  .p_context = NULL, .p_extend = &g_ether0_extended_cfg_t, };

/* Instance structure to use this module. */
const ether_instance_t g_ether0 =
{ .p_ctrl = &g_ether0_ctrl, .p_cfg = &g_ether0_cfg, .p_api = &g_ether_on_rmac, };
void g_hal_init(void)
{
    g_common_init ();
}
