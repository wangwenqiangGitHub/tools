#include <iostream>
#include <stdio.h>

typedef union radar_state {
  struct {
      uint64_t Reserved:6;
      uint64_t RadarState_NVMReadStatus:1;
      uint64_t RadarState_NVMwriteStatus:1;
      uint64_t RadarState_MaxDistanceCfg1:8;
      uint64_t Reserved2:1;
      uint64_t RadarState_Voltage_Error:1;
      uint64_t RadarState_Temporary_Error:1;
      uint64_t RadarState_Temperature_Error:1;
      uint64_t RadarState_Interference:1;
      uint64_t RadarState_Persistent_Error:1;
      uint64_t RadarState_MaxDistanceCfg2:2;
      uint64_t RadarState_RadarPowerCfg1:2;
      uint64_t Reserved3:6;
      uint64_t RadarState_SensorID:3;
      uint64_t Reserved4:1;
      uint64_t RadarState_SortIndex:3;
      uint64_t RadarState_RadarPowerCfg2:1;
      uint64_t Reserved5:1;
      uint64_t RadarState_CtrlRelayCfg:1;
      uint64_t RadarState_OutputTypeCfg:2;
      uint64_t RadarState_SendQualityCfg:1;
      uint64_t RadarState_SendExtInfoCfg:1;
      uint64_t RadarState_MotionRxState:2;
      uint64_t Reserved6:8;
      uint64_t Reserved7:2;
      uint64_t RadarState_RCS_Threshold:3;
      uint64_t Reserved8:3;
    } data = {};

  uint8_t raw_data[8];
} radar_state;

struct can_data{
	uint8_t tag;
	uint8_t len;
	uint8_t data[256];
};
#pragma pack(push, 1)
template <int N>
union direct_or_indirect {
	char direct[N];
	struct {
		char* indirect;
		size_t capacity;
	} indirect_content;
};
#pragma pack(pop)
#include <cstdint>
#include <cstring> // 用于std::memcpy

#pragma pack(push, 1)
template<int N>
struct ProtocolMessage {
	uint8_t type;
	uint8_t length;
	uint16_t sequence_number;
	uint8_t zone_number;
	uint16_t setting_type;

	struct Setting {
		uint8_t sequence;
		uint8_t property;
		uint16_t value;
	};

	Setting settings[N];

	uint16_t crc;
	uint8_t checksum;
};
#pragma pack(pop)
void test()
{
	// 假设N已经确定
	constexpr int N = 5; /* 替换为实际的定值数量 */;
	// 通道传来的消息和长度
	char* data;
	size_t len;

	// 检查消息长度是否匹配结构体大小
	if (len == sizeof(ProtocolMessage<N>)) {
		// 创建ProtocolMessage实例
		ProtocolMessage<N> message;

		// 直接通过内存拷贝赋值给结构体
		std::memcpy(&message, data, len);

		// 现在message已经包含了从data拷贝过来的数据
		// 可以对message进行进一步的处理或使用
		//
	} else {
		// 消息长度不正确，处理错误情况
	}
}

void can_read()
{
}
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
int main(int argc, char *argv[])
{
	int n = 0;
	if (n > 0)
	{
		printf("<%s-%s-%d>\n",__FILENAME__,__func__, __LINE__);
	}
	return 0;
}
