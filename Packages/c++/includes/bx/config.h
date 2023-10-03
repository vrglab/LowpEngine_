/*
 * Copyright 2010-2023 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bx/blob/master/LICENSE
 */

#ifndef BX_CONFIG_H_HEADER_GUARD
#define BX_CONFIG_H_HEADER_GUARD

#ifndef BX_CONFIG_DEBUG

#endif // BX_CONFIG_DEBUG

#ifndef BX_CONFIG_ALLOCATOR_DEBUG
#	define BX_CONFIG_ALLOCATOR_DEBUG BX_CONFIG_DEBUG
#endif // BX_CONFIG_ALLOCATOR_DEBUG

#ifndef BX_CONFIG_SUPPORTS_THREADING
#	define BX_CONFIG_SUPPORTS_THREADING !(0 \
			|| BX_PLATFORM_EMSCRIPTEN       \
			)
#endif // BX_CONFIG_SUPPORTS_THREADING

#endif // BX_CONFIG_H_HEADER_GUARD
