#include "hepch.h"
#include "HelloEngine.h"

#include "imgui/imgui.h"
class ExampleLayer : public HelloEngine::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		m_VertexArray.reset(HelloEngine::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<HelloEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(HelloEngine::VertexBuffer::Create(vertices, sizeof(vertices)));

		HelloEngine::BufferLayout layout = {
			{HelloEngine::ShaderDataType::Float3, "a_Position"},
			{HelloEngine::ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<HelloEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(HelloEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexShaderSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentShaderSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new HelloEngine::Shader(vertexShaderSrc, fragmentShaderSrc));

		float blueVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		m_BlueVertexArray.reset(HelloEngine::VertexArray::Create());

		std::shared_ptr<HelloEngine::VertexBuffer> blueVertexbuffer(HelloEngine::VertexBuffer::Create(blueVertices, sizeof(blueVertices)));
		blueVertexbuffer->SetLayout({
			{ HelloEngine::ShaderDataType::Float3, "aPosition" }
			});
		m_BlueVertexArray->AddVertexBuffer(blueVertexbuffer);

		uint32_t blueIndices[6] = { 0,1,2,2,3,0 };
		std::shared_ptr<HelloEngine::IndexBuffer> blueIndexbuffer(HelloEngine::IndexBuffer::Create(blueIndices, sizeof(blueIndices) / sizeof(uint32_t)));
		m_BlueVertexArray->SetIndexBuffer(blueIndexbuffer);

		std::string blueVertexShaderSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueFragmentShaderSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader = std::make_shared<HelloEngine::Shader>(blueVertexShaderSrc, blueFragmentShaderSrc);
	}

	virtual void OnUpdate(const HelloEngine::Timestep& ts) override
	{
		if (HelloEngine::Input::IsKeyPressed(HE_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if(HelloEngine::Input::IsKeyPressed(HE_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (HelloEngine::Input::IsKeyPressed(HE_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (HelloEngine::Input::IsKeyPressed(HE_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (HelloEngine::Input::IsKeyPressed(HE_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (HelloEngine::Input::IsKeyPressed(HE_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		HelloEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		HelloEngine::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		HelloEngine::Renderer::BeginScene(m_Camera);

		HelloEngine::Renderer::Submit(m_BlueShader, m_BlueVertexArray);
		HelloEngine::Renderer::Submit(m_Shader, m_VertexArray);

		HelloEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
	}

	virtual void OnEvent(HelloEngine::Event& event) override
	{
	}
private:
	std::shared_ptr<HelloEngine::Shader> m_Shader;
	std::shared_ptr<HelloEngine::VertexArray> m_VertexArray;

	std::shared_ptr<HelloEngine::Shader> m_BlueShader;
	std::shared_ptr<HelloEngine::VertexArray> m_BlueVertexArray;

	HelloEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition = glm::vec3(0.0f);
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 45.0f;
};


class Sandbox: public HelloEngine::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}

private:

};


HelloEngine::Application* HelloEngine::CreateApplication()
{
	return new Sandbox;
}
