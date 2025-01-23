#pragma once

#include <string>
#include <type_traits>
#include <vector>
#include <mutex>

namespace afx
{

struct iAsset
{
	std::string path;
	uint32_t ref_count;
};

class ResourceManager
{
public:
	ResourceManager() {
		m_searchPaths.push_back( "./" );
	}

	template<typename _Ty, typename... _Args>
	_Ty* load( const std::string& _path, _Args... _args ) {
		static_assert( std::is_base_of<iAsset2, _Ty>::value, "Object '_Ty' must inherit from iAsset2" );
		
		std::lock_guard lock{ m_mutex };

		_Ty* asset = _loadImpl<_Ty, _Args...>( _path, _args... );
		if( asset == nullptr ) // error
			return nullptr;

		asset->path = _path;
		m_loadedAssets.push_back( reinterpret_cast<iAsset2*>( asset ) );
		printf( "Loaded %s\n", _path.c_str() );

		return asset;
	}

	template<typename _Ty>
	void unload( _Ty** _pAsset ) {
		static_assert( std::is_base_of<iAsset2, _Ty>::value, "Object '_Ty' must inherit from iAsset2" );
		if( _pAsset == nullptr || *_pAsset == nullptr )
			return; // cannot unload nullptr

		std::lock_guard lock{ m_mutex };

		for( auto it = m_loadedAssets.begin(); it != m_loadedAssets.end(); ++it )
		{
			if( *it != reinterpret_cast<iAsset2*>( *_pAsset ) )
				continue;

			m_loadedAssets.erase( it );

			_unloadImpl<_Ty>( *_pAsset );
			printf( "Unloaded %s\n", (*_pAsset)->path.c_str() );

			delete *_pAsset;
			*_pAsset = nullptr;

			return;
		}

		printf( "Asset was not loaded in this asset manager!" );
	}
	
	template<typename _Ty, typename... _Args>
	_Ty* _loadImpl( const std::string& _path, _Args... _args );
	
	template<typename _Ty>
	void _unloadImpl( _Ty* );

private:
	std::vector<std::string> m_searchPaths{};
	std::vector<std::pair<std::string, iAsset*>> m_loadedAssets{};
	
	std::mutex m_mutex{};
};

}




// other file


template<>
ShaderModule* afx::ResourceManager::_loadImpl<ShaderModule>( const std::string& _path )
{
	uint32_t data_size = 0;
	uint8_t* data = fileLoad( _path, &data_size );

	if( data_size == 0 )
	{
		printf( " Failed to load Shader Module: %s\n", _path.c_str() );
		return {};
	}

	cGraphicsDevice& device;

	TgrShaderModuleDesc desc{};
	desc.pCode = reinterpret_cast<uint32_t*>( data );
	desc.codeSize = data_size;

	ShaderModule* shader_module = new ShaderModule();
	shader_module->shader_module = device.createShaderModule( &desc );
	
	
	free( data );

	return shader_module;
}