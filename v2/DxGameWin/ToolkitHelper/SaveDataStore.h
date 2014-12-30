#pragma once
#include "pch.h"
#include <ppltasks.h>

using namespace std;
using namespace Windows::Storage;
using namespace Microsoft::WRL;
using namespace concurrency;
using namespace Windows::Foundation::Collections;
using namespace SerializeWrapper;
using namespace Windows::Storage::Streams;

namespace ToolkitHelper{

	
	template<typename T>
	class SaveDataStore{
	public:

		static shared_ptr<SaveDataStore<T>> getInstance(){
			if (m_instance != nullptr){
				return m_instance;
			}
			else{
				m_instance = shared_ptr<SaveDataStore<T>>(new SaveDataStore<T>());
				return m_instance;
			}
		}

		static void resetInstance(){
			if (m_instance != nullptr){
				m_instance.reset();
				m_instance = nullptr;
			}
		}

		T^ GetData(){
			return m_dataModel;
		}


		task<bool> LoadDataAsync(){
			return create_task(m_folder->GetFilesAsync())
				.then([this](IVectorView<StorageFile^>^ list){
				bool isFileExist = false;
				for (StorageFile^ file : list){
					if (file->Name->Equals(m_fileName)){
						isFileExist = true;
					}
				}

				/*if (isFileExist){
					return create_task(m_folder->CreateFileAsync(m_fileName))
					.then([this](StorageFile^ file){

					return create_task(file->OpenAsync(FileAccessMode::Read))
					.then([this](IRandomAccessStream^ stream){
					Serializer^ serializer = ref new Serializer(T);
					Object^ obj = serializer->Read(stream->GetOutputStreamAt(0));

					this->SetData(obj);
					stream->FlushAsync();
					stream->Dispose();
					});
					});
					}
					else{
					return create_task(m_folder->CreateFileAsync(m_fileName))
					.then([this](StorageFile^ file){

					return create_task(file->OpenAsync(FileAccessMode::Read))
					.then([this](IRandomAccessStream^ stream){
					Serializer^ serializer = ref new Serializer(T);
					serializer->Write(stream->GetOutputStreamAt(0), *this->GetData().get());
					stream->FlushAsync();
					stream->Dispose();
					});
					});
					}*/
			});

		}



		task<void> SaveDataAsync(){

			return create_task(m_folder->CreateFileAsync(m_fileName, CreationCollisionOption::ReplaceExisting))
				.then([this](StorageFile^ file){

				return create_task(file->OpenAsync(FileAccessMode::ReadWrite))
					.then([this](IRandomAccessStream^ stream){
					Serializer^ serializer = ref new Serializer(((Object^)m_dataModel)->GetType());
					serializer->Write(stream->GetOutputStreamAt(0), this->GetData());
					stream->FlushAsync();
					//stream->Dispose();
					
				});
			});
		}


	private:
		SaveDataStore(){
			m_dataModel = ref new T();
			m_folder = KnownFolders::CameraRoll;
			m_fileName = L"SaveDataStoreData";
		}

		T^ m_dataModel;

		StorageFile^ m_file;
		StorageFolder^ m_folder;
		String^ m_fileName;
		
		static shared_ptr<SaveDataStore<T>> m_instance;

		
	};

}