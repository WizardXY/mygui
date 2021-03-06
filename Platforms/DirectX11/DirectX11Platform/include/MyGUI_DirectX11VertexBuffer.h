/*!
	@file
	@author		Ustinov Igor aka Igor', DadyaIgor
	@date		09/2011
*/

#ifndef MYGUI_DIRECTX11_VERTEX_BUFFER_H_
#define MYGUI_DIRECTX11_VERTEX_BUFFER_H_

#include "MyGUI_Prerequest.h"
#include "MyGUI_IVertexBuffer.h"
#include "MyGUI_DirectX11RenderManager.h"

struct ID3D11Buffer;

namespace MyGUI
{

	class DirectX11VertexBuffer : public IVertexBuffer
	{
	public:
		DirectX11VertexBuffer(DirectX11RenderManager* _pRenderManager);
		~DirectX11VertexBuffer() override;

		void setVertexCount(size_t _count) override;
		size_t getVertexCount() const override;

		Vertex* lock() override;
		void unlock() override;

	private:
		void create();
		void destroy();
		void resize();

	private:
		DirectX11RenderManager* mManager;
		size_t mVertexCount;
		size_t mNeedVertexCount;

	public:
		ID3D11Buffer* mBuffer;
	};

} // namespace MyGUI

#endif // MYGUI_DIRECTX11_VERTEX_BUFFER_H_
