#pragma once
#include <string>
#include <unordered_map>

namespace Engine 
{
	class ENGINE_API Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbuind() const = 0;

		virtual const std::string& GetName() const = 0;
		
		static Ref<Shader> Create(const std::string& vertexSrc, const std::string& fragmentSrc, const std::string& name = "Shader");
		static Ref<Shader> Create(const std::string& filePath);
	};

	class ENGINE_API ShaderLibrary
	{
	public:
		void Add(const Ref<Shader>& shader);
		void Add(const std::string& name, const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& name, const std::string& filePath);
		Ref<Shader> Load(const std::string& filePath);
		Ref<Shader> Get(const std::string& name);
	private:
		std::unordered_map<std::string, Ref<Shader>> mShaders;
	};
}