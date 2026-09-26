# stm_common

STM32 组件共享的基础定义，当前只提供 `stm_err.h`，不依赖 HAL、RTOS、日志或 C 运行库分配器。

## 接入

```sh
git clone https://github.com/NingZiXi/stm_common.git Lib/stm_common
```

需要 `stdint.h`，无编译源文件。与 [stm_sdram](https://github.com/NingZiXi/stm_sdram)、[stm_flash](https://github.com/NingZiXi/stm_flash) 一起使用：

```cmake
add_subdirectory(Lib/stm_common)
add_subdirectory(Lib/stm_sdram)
add_subdirectory(Lib/stm_flash)
target_link_libraries(your_firmware PRIVATE stm_sdram stm_flash)
```

各组件独立使用时可将 `stm_common` 放在其同级目录，或提前定义此 CMake target。手动集成时将此目录加入头文件搜索路径。不要在两个库里分别复制一套错误码。

## 错误码约定

`stm_err_t` 是 `int32_t`。`STM_OK=0`，其他已定义值均为非零正数；用 `err != STM_OK` 检查失败，不能用 `err < 0`。具体值显式固定，发布后不重排。

| 数值 | 名称 | 含义 |
|---|---|---|
| 0 | STM_OK | 成功 |
| 0x0101 | STM_ERR_INVALID_ARG | 空指针、无效参数或对齐 |
| 0x0102 | STM_ERR_INVALID_STATE | 外设已占用、输出句柄非空、实例故障停用 |
| 0x0103 | STM_ERR_NO_MEM | 无法分配控制对象 |
| 0x0104 | STM_ERR_TIMEOUT | HAL 或设备忙超时 |
| 0x0105 | STM_ERR_IO | HAL_ERROR/HAL_BUSY 或通信失败 |
| 0x0106 | STM_ERR_NOT_SUPPORTED | 不支持的器件 |
| 0x0107 | STM_ERR_INVALID_CONFIG | 外设或芯片配置不符合要求 |
| 0x0108 | STM_ERR_OUT_OF_RANGE | 存储范围越界 |
| 0x0109 | STM_ERR_INVALID_CONTEXT | 不允许的中断上下文或屏蔽状态 |
| 0x010A | STM_ERR_VERIFY | 数据校验失败 |
| 0x010B | STM_ERR_CANCELLED | 调用者取消 |

公共错误保留 `0x0100–0x0FFF`。`0x1000–0x10FF` 分配给 Flash 专用错误；实际定义在 `stm_flash.h`。`0x1100–0x11FF` 分配给 ESP-AT 专用错误：`ESP_AT_ERR_PROTO=0x1101`（协议格式无效）、`ESP_AT_ERR_RESP=0x1102`（模块返回 ERROR/FAIL），定义在 `esp_at_types.h`。`stm_ota` 当前仅复用公共错误，不占用专用区间。后续组件必须登记新的不重叠区间。返回码描述一次操作的结果，不是数据长度、HAL 枚举或芯片状态寄存器。

`tests/test_allocator.h` 仅用于无 C 运行库的 ARM 模拟测试，提供分配失败注入和泄漏/重复释放检查，不得加入产品固件。

## 许可

采用 [MIT License](LICENSE)。
