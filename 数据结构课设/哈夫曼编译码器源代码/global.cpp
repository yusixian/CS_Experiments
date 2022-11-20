#include "global.h" 
HufTree huf;
void Init() {							  //初始化
	system("mode con cols=96 lines=35");  //改变宽高
	system("color F0");					  //改变控制台窗口颜色
	system("cls");						//清屏
}
void MainInterface() {
	while (1) {
		menus.Menu1();
		switch (_getch()) {							
			case '1': CreateHfmTree(); break;		// 1.建立哈夫曼树，并将其存入文件HfmTree中
			case '2': O.Encoding(); break;	// 2. 哈夫曼编码 对文件ToBeTran中的正文进行编码
			case '3': O.Decoding(); break;	// 3. 哈夫曼译码 将文件CodeFile的内容译码后以文本形式显示在终端上，译文存入文件TextFile
			case '4': O.PrintCompreRatio(); break;	// 4. 显示译码后压缩率与平均压缩长度
			case '5': O.Search(); break;	// 5. 查询某字符对应编码功能
			case '6': O.PrintHfmTree(); break;	// 6. 展示哈夫曼树
			case '7': O.ExportHfmCode(); break;	// 7. 导出哈夫曼编码到CorresponCode文件中
			case '8': exit(0); break;  // 8. 退出
			case 27: exit(0); break;			// ESC.退出
			default: break;
		}
	}
}
//建立哈夫曼树
void CreateHfmTree() {
	while (1) {
		menus.Menu2();
		switch (_getch()) {
			case '1': O.CreateHfmTreeByInput(); break;	
			// 1.从终端读入字符及其权值直接建立哈夫曼树
			case '2': O.CreateHfmTreeByFile(); break;		  
			// 2. 读取字符文件建立最优哈夫曼树
			case 27: return;  // ESC.返回上一步
			default: break;
		}
	}
}