package main

import (
	settings "bluebell/config"
	"fmt"
)

// Go Web 开发较通用的脚手架模板

func main() {
	// 1. 加载配置
	if err := settings.Init(); err != nil {
		fmt.Printf("Init settings err: %v\n", err)
		return
	}

	// 2. 初始化日志
	if err = logger.Init(); err != nil {
		fmt.Printf("Init logger err: %v\n", err)
		return
	}

	// 3. 初始化mysql连接
	if err = mysql.Init(); err != nil {
		fmt.Printf("Init mysql err: %v\n", err)
		return
	}

	// 4. 初始化redis连接
	if err = redis.Init(); err != nil {
		fmt.Printf("Init redis err: %v\n", err)
		return
	}

	// 5. 注册路由
	
	// 6. 启动服务（优雅关机）

}
