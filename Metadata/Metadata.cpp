// Metadata.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

// 避免 ssize_t 引发的错误
#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#include <iostream>  
#include <vlc/vlc.h>

using namespace std;

// 读取元数据
void reading(libvlc_media_t *media)
{
	// 读取标题、艺术家、专辑
	char *title = libvlc_media_get_meta(media, libvlc_meta_Title);
	char *artist = libvlc_media_get_meta(media, libvlc_meta_Artist);
	char *album = libvlc_media_get_meta(media, libvlc_meta_Album);

	if (title != NULL)
		cout << "title: " << title << endl;

	if (artist != NULL)
		cout << "artist: " << artist << endl;

	if (album != NULL)
		cout << "album: " << album << endl;
}

// 更改元数据
void writing(libvlc_media_t *media)
{
	// 设置元数据
	libvlc_media_set_meta(media, libvlc_meta_Title, "Title");
	libvlc_media_set_meta(media, libvlc_meta_Artist, "Artist");
	libvlc_media_set_meta(media, libvlc_meta_Album, "Album");

	// 保存元数据
	libvlc_media_save_meta(media);
}

int main()
{
	libvlc_instance_t *vlcInstance;
	libvlc_media_t *media;

	// 创建并初始化 libvlc 实例
	vlcInstance = libvlc_new(0, NULL);

	// 创建一个 media，参数是一个媒体资源位置（例如：有效的 URL）。 
	media = libvlc_media_new_path(vlcInstance, "E:\\Music\\It's My Life.mp3");

	// 解析媒体以从中读取信息
	libvlc_media_parse(media);

	cout << "---------- Before ----------" << endl;

	// 读取元数据
	reading(media);

	//// 写入元数据
	//writing(media);

	cout << "---------- After ----------" << endl;

	//// 再次读取元数据
	//reading(media);

	// 现在，不需要保留 media 了
	libvlc_media_release(media);

	// 释放 libvlc 实例
	libvlc_release(vlcInstance);

	getchar();

	return 0;
}