/*********************************************警察表********************************************/
-- 删除旧的警察表，如果存在
DROP TABLE IF EXISTS "tbl_police";

-- 创建新的警察表
CREATE TABLE "tbl_police"(
    "police_id" integer PRIMARY KEY AUTOINCREMENT,
    "police_name" varchar(20) NOT NULL,
    "police_number" varchar(11) NOT NULL UNIQUE, -- 增加 UNIQUE 约束，确保警员编号唯一
    "police_pwd" varchar(35) DEFAULT 'e10adc3949ba59abbe56e057f20f883e',
    "police_status" integer DEFAULT 0, -- 0表示未登录，1表示已登录
    "createTime" varchar(20)
);

-- 初始化三个警察信息
INSERT INTO "tbl_police" VALUES (1,'小明','omo240301','e10adc3949ba59abbe56e057f20f883e',0,'2024-08-17 15:05:00');
INSERT INTO "tbl_police" VALUES (2,'小宏','omo240302','e10adc3949ba59abbe56e057f20f883e',0,'2024-08-17 15:08:00');
INSERT INTO "tbl_police" VALUES (3,'小强','omo240303','e10adc3949ba59abbe56e057f20f883e',0,'2024-08-17 15:09:00');

/*********************************************视频表********************************************/
-- 删除旧的视频表，如果存在
DROP TABLE IF EXISTS "tbl_video";

-- 创建新的视频表
CREATE TABLE "tbl_video"(
    "video_id" integer PRIMARY KEY AUTOINCREMENT,
    "video_name" varchar(20) NOT NULL,
    "video_path" varchar(40) NOT NULL,
    "videoTime" varchar(20) NOT NULL, -- 视频的总时长
    "video_shootTime" varchar(20) NOT NULL, -- 拍摄时间（什么时候拍的）
    "police_number" varchar(11) NOT NULL,
    "firstPhoto_path" varchar(20) NOT NULL,
    FOREIGN KEY ("police_number") REFERENCES "tbl_police" ("police_number")
);

/*********************************************照片表********************************************/
-- 删除旧的照片表，如果存在
DROP TABLE IF EXISTS "tbl_photo";

-- 创建新的照片表
CREATE TABLE "tbl_photo"(
    "photo_id" integer PRIMARY KEY AUTOINCREMENT,
    "photo_name" varchar(20) NOT NULL,
    "photo_path" varchar(40) NOT NULL,
    "photo_shootTime" varchar(20) NOT NULL, -- 拍摄时间
    "police_number" varchar(11) NOT NULL,
    FOREIGN KEY ("police_number") REFERENCES "tbl_police" ("police_number")
);

/*********************************************设备表********************************************/
-- 删除旧的设备表，如果存在
DROP TABLE IF EXISTS "tbl_equipment";

-- 创建新的设备表
CREATE TABLE "tbl_equipment"(
    "equipment_id" integer PRIMARY KEY AUTOINCREMENT,
    "equipment_name" varchar(20) NOT NULL,
    "equipment_number" varchar(20) NOT NULL UNIQUE, -- 增加 UNIQUE 约束，确保设备编号唯一
    "equipment_status" integer DEFAULT 0 -- 0表示空闲，1表示使用中
);

-- 初始化三个设备信息
INSERT INTO "tbl_equipment" VALUES (1,'设备1','STCF89G02',0);
INSERT INTO "tbl_equipment" VALUES (2,'设备2','STC8UFO',0);
INSERT INTO "tbl_equipment" VALUES (3,'设备3','STC89C52',0);

/*********************************************日志表********************************************/
-- 删除旧的日志表，如果存在
DROP TABLE IF EXISTS "tbl_log";

-- 创建新的日志表
CREATE TABLE "tbl_log" (
    "log_id" INTEGER PRIMARY KEY AUTOINCREMENT,
    "operationType" VARCHAR(20) NOT NULL,
    "writeTime" VARCHAR(20) NOT NULL,
    "equipment_number" VARCHAR(20) NOT NULL,
    "police_number" VARCHAR(11) NOT NULL,
    FOREIGN KEY ("equipment_number") REFERENCES "tbl_equipment" ("equipment_number"),
    FOREIGN KEY ("police_number") REFERENCES "tbl_police" ("police_number")
);

/*********************************************设置表********************************************/
-- 删除旧的设置表，如果存在
DROP TABLE IF EXISTS "tbl_setting";

-- 创建新的设置表
CREATE TABLE "tbl_setting" (
    "set_id" INTEGER PRIMARY KEY AUTOINCREMENT,
    "videoPath" VARCHAR(40) NOT NULL,
    "photoPath" VARCHAR(40) NOT NULL,
    "equipment_number" VARCHAR(20) NOT NULL
);