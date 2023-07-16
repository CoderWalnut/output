package settings

import (
	"fmt"

	"github.com/fsnotify/fsnotify"
	"github.com/spf13/viper"
)

func Init() (err error) {
	viper.SetConfigName("config")
	viper.SetConfigType("yaml")
	viper.AddConfigPath("./")

	err = viper.ReadInConfig()
	if err != nil {
		fmt.Printf("Viper read config err: %v\n", err)
		return
	}

	// 热加载新的配置更改
	viper.WatchConfig()
	viper.OnConfigChange(func(in fsnotify.Event) {
		fmt.Println("配置文件修改...")
	})

	return
}
