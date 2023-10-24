/* ======================================================================================== */
/* LowpEngine - Core C/C++ header file.														*/
/*                                                                                          */
/*                 Copyright (c) 2023-Present Arad Bozorgmehr (Vrglab)                      */
/*                                                                                          */
/* Authors: Arad Bozorgmehr(Vrglab)                                                         */
/* ======================================================================================== */
#pragma once

#include <LowpCommons.h>
#ifdef _WIN32
#include <Windows.h>
#include <d3d12.h>
#include <D3Dcompiler.h>
#include <dxgi1_4.h>
#include <DirectXColors.h>
#include <DirectXMath.h>
#endif

#ifdef __d3d12_h__
LP_Export struct Dx12RenderingResources
{
	ID3D12Resource* renderTarget; // This should be your swap chain's buffer
	ID3D12Resource* depthStencilBuffer;

	ID3D12DescriptorHeap* rtvHeap;
	ID3D12DescriptorHeap* dsvHeap;

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle;
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle;
};
#endif