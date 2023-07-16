package main

import (
	"time"

	"github.com/bwmarrin/snowflake"
)

var node *snowflake.Node

/*
startTime: 指定起始时间 YYYY-MM-DD
machineId: 分布式系统中单个机器标识
*/
func Init(startTime string, machineId int64) (err error) {
	var st time.Time
	st, err = time.Parse("2006-01-02", startTime)
	if err != nil {
		return
	}

	// 时间戳单位为 ms
	snowflake.Epoch = st.UnixNano() / 1000000
	node, err = snowflake.NewNode(machineId)
	return
}

func GenId() int64 {
	return node.Generate().Int64()
}

/*
func main() {
	if err := Init("2023-07-15", 1); err != nil {
		fmt.Printf("Init failure, err: %v\n", err)
		return
	}

	id := GenId()
	fmt.Println(id)
}
*/
