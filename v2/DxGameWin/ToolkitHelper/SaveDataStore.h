#pragma once
#include "pch.h"
#include <ppltasks.h>

using namespace std;
using namespace Windows::Storage;
using namespace Microsoft::WRL;
using namespace concurrency;
using namespace Windows::Foundation::Collections;


template<typename T>
class SaveDataStore{
public:
	static shared_ptr<SaveDataStore> getInstance(){
		if (m_instance != nullptr){
			return m_instance;
		}
		else{
			m_instance = shared_ptr<SaveDataStore>(new SaveDataStore());
			return m_instance;
		}
	}

	static void resetInstance(){
		if (m_instance != nullptr){
			m_instance.reset();
			m_instance = nullptr;
		}
	}

	shared_ptr<T> GetData(){
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

			if (isFileExist){
				return create_task(m_folder->GetFileAsync())
					.then([this](StorageFile^ file){
					//AddSerialize Method
				});
			}
			else{
				return create_task(m_folder->CreateFileAsync(m_fileName))
					.then([this](StorageFile^ file){
					//AddSerialize Method
				});
			}
		});
		
	}

	task<void> SaveDataAsync(){
		return create_task(m_folder->CreateFileAsync(m_fileName, CreationCollisionOption::ReplaceExisting))
			.then([this](StorageFile^ file){
			//Add Seialize Method
		});
	}
private:
	SaveDataStore(){
		m_dataModel = shared_ptr<T>(new T());
		m_folder = ApplicationData::LocalFolder;
		m_fileName = L"SaveDataStoreData";
	}

	shared_ptr<T> m_dataModel;
	
    StorageFile^ m_file;
	StorageFolder^ m_folder;
	Stiring^ m_fileName;

	static shared_ptr<SaveDataStore> m_instance;
};