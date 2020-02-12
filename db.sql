DROP INDEX "main"."idx_friendid";

DROP TABLE "main"."sqlite_sequence";
DROP TABLE "main"."sqlite_stat1";
DROP TABLE "main"."t_friends";
DROP TABLE "main"."t_friendshistory";
DROP TABLE "main"."t_person";
DROP TABLE "main"."t_pmsg";
DROP TABLE "main"."t_pmsghis";
DROP TABLE "main"."t_group";
DROP TABLE "main"."t_groupmembers";

CREATE TABLE "main"."sqlite_sequence" (
"name" ,
"seq" 
);
CREATE TABLE "main"."sqlite_stat1" (
"tbl" ,
"idx" ,
"stat" 
);
CREATE TABLE "main"."t_friends" (
"RowID" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
"FriendID" INTEGER NOT NULL,
"MakeTime" BIGINT NOT NULL,
CONSTRAINT "fk_t_friends_t_person_1" FOREIGN KEY ("FriendID") REFERENCES "t_person" ("ID")
);
CREATE INDEX "main"."idx_friendid" ON "t_friends" ("FriendID");

CREATE TABLE "main"."t_friendshistory" (
"RowID" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
"FriendID" INTEGER NOT NULL,
"Operator" INTEGER NOT NULL,
"OperatorTime" BIGINT NOT NULL,
"CreateTime" BIGINT NOT NULL,
"Status" INTEGER NOT NULL,
CONSTRAINT "fk_t_friendshistory_t_friends_1" FOREIGN KEY ("FriendID") REFERENCES "t_friends" ("FriendID")
);
CREATE TABLE "main"."t_person" (
"RowID" INTEGER NOT NULL,
"ID" INTEGER NOT NULL,
"NickName" VARCHAR,
"Signature" VARCHAR,
"Gender" INTEGER,
"Constellations" INTEGER,
"Birthday" REAL,
"Mobile" VARCHAR,
"Tel" VARCHAR,
"Email" VARCHAR,
"RegisterTime" BIGINT,
"CreateTime" BIGINT,
PRIMARY KEY ("ID") 
);
CREATE TABLE "main"."t_pmsg" (
"RowID" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
"MsgType" INTEGER NOT NULL,
"Content" VARCHAR,
"Sender" INTEGER NOT NULL,
"Receiver" INTEGER,
"TimeStamp" BIGINT,
"MsgStatus" INTEGER NOT NULL,
"CreateTime" BIGINT NOT NULL
);
CREATE TABLE "main"."t_pmsghis" (
"RowID" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
"MsgType" INTEGER NOT NULL,
"Content" VARCHAR,
"Sender" INTEGER NOT NULL,
"Receiver" INTEGER,
"TimeStamp" BIGINT,
"MsgStatus" INTEGER NOT NULL,
"CreateTime" BIGINT NOT NULL
);
CREATE TABLE "main"."t_group" (
"RowID" INTEGER NOT NULL,
"ID" INTEGER NOT NULL,
"Name" TEXT NOT NULL,
"Owner" INTEGER,
"CreateTime" INTEGER,
PRIMARY KEY ("ID") 
);
CREATE TABLE "main"."t_groupmembers" (
"RowID" INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
"GroupID" INTEGER,
"MemberID" INTEGER,
"MemberIdentity" INTEGER,
"JoinTime" INTEGER,
"CreateTime" INTEGER,
CONSTRAINT "fk_t_groupmembers_t_group_1" FOREIGN KEY ("GroupID") REFERENCES "t_group" ("ID") ON DELETE CASCADE ON UPDATE CASCADE,
CONSTRAINT "fk_t_groupmembers_t_person_1" FOREIGN KEY ("MemberID") REFERENCES "t_person" ("ID")
);
