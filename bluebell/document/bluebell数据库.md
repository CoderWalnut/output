## 一、数据表

### （一）用户表

```sql
CREATE TABLE user ( 
    id BIGINT NOT NULL PRIMARY KEY AUTO_INCREMENT,
    userId BIGINT NOT NULL UNIQUE,
    userName VARCHAR(64) NOT NULL UNIQUE,
    password VARCHAR(64) NOT NULL,
    email VARCHAR(64) NOT NULL,
    gender ENUM('男', '女') NOT NULL,
    createTime TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
    updateTime TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP
);
```

将userId设置为BIGINT类型是不合理的：

1. 不要将userId设置为AUTO_INCREMENT，如果是自增的话，新用户注册会拿到自己的userId，这样就会知道你的网站的用户数量；

2. 当使用分库分表时，分成不同的库，不同的库的userId就可能重复。

**分布式ID生成器**

- 全局唯一性：不能出现有重复的ID标识
- 递增性：确保生成ID对于用户或业务是递增的
- 高可用性：确保任何时候都能生成正确的ID
- 高性能性：在高并发的环境下依然表现良好

不仅仅是用于用户ID，实际互联网中有很多场景需到能够生成类似MySQL自增ID这样不断增大，同时又不会重复的id，以支持业务中的高并发场景。
比较典型的场景有：电商促销时短时间内会有大量的订单涌入到系统，比如每秒10w+；明星出轨时微博短时间内会产生大量的相关微博转发和评论消息。在这些业务场景下将数据插入数据库之前，我们需要给这些订单和消息先分配一个唯一ID，然后再保存到数据库中。对这个id的要求是希望其中能带有一些时间信息，这样即使我们后端的系统对消息进行了分库分表，也能够以时间顺序对这些消息进行排序。

**snowflake算法介绍**

雪花算法，它是Twitter开源的由64位整数组成的分布式ID，性能较高，并且在单机上递增。

![image-20230715110308033](C:\Users\19871\AppData\Roaming\Typora\typora-user-images\image-20230715110308033.png)