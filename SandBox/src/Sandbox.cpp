#include "HelloEngine.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"
class ExampleLayer : public HelloEngine::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_CameraController(1280.0f / 720.0f)
	{
		m_VertexArray.reset(HelloEngine::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, -1.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, -1.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, -1.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		HelloEngine::Ref<HelloEngine::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(HelloEngine::VertexBuffer::Create(vertices, sizeof(vertices)));

		HelloEngine::BufferLayout layout = {
			{HelloEngine::ShaderDataType::Float3, "a_Position"},
			{HelloEngine::ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		HelloEngine::Ref<HelloEngine::IndexBuffer> indexBuffer;
		indexBuffer.reset(HelloEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexShaderSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

		m_Shader = HelloEngine::Shader::Create("VertexPosColor", vertexShaderSrc, fragmentShaderSrc);

		float FlatColorVertices[5 * 4] = {
			-0.5f, -0.5f, -0.2f, 0.0f, 0.0f,
			 0.5f, -0.5f, -0.2f, 1.0f, 0.0f,
			 0.5f,  0.5f, -0.2f, 1.0f, 1.0f,
			-0.5f,  0.5f, -0.2f, 0.0f, 1.0f
		};

		m_FlatColorVertexArray.reset(HelloEngine::VertexArray::Create());

		HelloEngine::Ref<HelloEngine::VertexBuffer> FlatColorVertexbuffer(HelloEngine::VertexBuffer::Create(FlatColorVertices, sizeof(FlatColorVertices)));
		FlatColorVertexbuffer->SetLayout({
			{ HelloEngine::ShaderDataType::Float3, "a_Position" },
			{ HelloEngine::ShaderDataType::Float2, "a_TexCoord" }
			});
		m_FlatColorVertexArray->AddVertexBuffer(FlatColorVertexbuffer);

		uint32_t FlatColorIndices[6] = { 0,1,2,2,3,0 };
		HelloEngine::Ref<HelloEngine::IndexBuffer> FlatColorIndexbuffer(HelloEngine::IndexBuffer::Create(FlatColorIndices, sizeof(FlatColorIndices) / sizeof(uint32_t)));
		m_FlatColorVertexArray->SetIndexBuffer(FlatColorIndexbuffer);

		std::string FlatColorVertexShaderSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string FlatColorFragmentShaderSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0f);
			}
		)";

		m_FlatColorShader = HelloEngine::Shader::Create("FlatColorShader", FlatColorVertexShaderSrc, FlatColorFragmentShaderSrc);
		HelloEngine::Ref<HelloEngine::Shader> textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = HelloEngine::Texture2D::Create("assets/textures/Checkerboard.png");
		m_ChernoLogoTexture = HelloEngine::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<HelloEngine::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<HelloEngine::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	virtual void OnUpdate(const HelloEngine::Timestep& ts) override
	{
		m_CameraController.OnUpdate(ts);

		HelloEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		HelloEngine::RenderCommand::Clear();

		HelloEngine::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.0f));

		std::dynamic_pointer_cast<HelloEngine::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<HelloEngine::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_FlatColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				HelloEngine::Renderer::Submit(m_FlatColorShader, m_FlatColorVertexArray, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.GetShader("Texture");

		m_Texture->Bind();
		HelloEngine::Renderer::Submit(textureShader, m_FlatColorVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_ChernoLogoTexture->Bind();
		HelloEngine::Renderer::Submit(textureShader, m_FlatColorVertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//Èý½ÇÐÎ
		//HelloEngine::Renderer::Submit(m_Shader, m_VertexArray);

		HelloEngine::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Setting");
		ImGui::ColorEdit3("Flat Color", glm::value_ptr(m_FlatColor));
		ImGui::End();
	}

	virtual void OnEvent(HelloEngine::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}
private:
	HelloEngine::ShaderLibrary m_ShaderLibrary;

	HelloEngine::Ref<HelloEngine::Shader> m_Shader;
	HelloEngine::Ref<HelloEngine::VertexArray> m_VertexArray;

	HelloEngine::Ref<HelloEngine::Shader> m_FlatColorShader;
	HelloEngine::Ref<HelloEngine::VertexArray> m_FlatColorVertexArray;

	HelloEngine::Ref<HelloEngine::Texture2D> m_Texture, m_ChernoLogoTexture;

	HelloEngine::OrthographicCameraController m_CameraController;

	glm::vec3 m_FlatColor = { 0.2f, 0.3f, 0.8f };
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
