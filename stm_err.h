/**
 * @file    stm_err.h
 * @brief   STM32 组件公共错误码
 */
#ifndef STM_ERR_H
#define STM_ERR_H

#include <stdint.h>

typedef int32_t stm_err_t;

#define STM_OK                  ((stm_err_t)0)      // 操作成功
#define STM_ERR_INVALID_ARG     ((stm_err_t)0x0101) // 参数、指针或对齐无效
#define STM_ERR_INVALID_STATE   ((stm_err_t)0x0102) // 当前状态不允许操作
#define STM_ERR_NO_MEM          ((stm_err_t)0x0103) // 分配对象失败
#define STM_ERR_TIMEOUT         ((stm_err_t)0x0104) // 操作超时
#define STM_ERR_IO              ((stm_err_t)0x0105) // HAL 或通信失败
#define STM_ERR_NOT_SUPPORTED   ((stm_err_t)0x0106) // 不支持的器件或模式
#define STM_ERR_INVALID_CONFIG  ((stm_err_t)0x0107) // 外设配置不满足要求
#define STM_ERR_OUT_OF_RANGE    ((stm_err_t)0x0108) // 偏移或长度越界
#define STM_ERR_INVALID_CONTEXT ((stm_err_t)0x0109) // 调用上下文不允许
#define STM_ERR_VERIFY          ((stm_err_t)0x010A) // 读回数据不一致
#define STM_ERR_CANCELLED       ((stm_err_t)0x010B) // 调用者取消操作

#endif
