DROP DATABASE IF EXISTS `OwbExecutorDb`;
CREATE DATABASE `OwbExecutorDb`;
USE `OwbExecutorDb`;

CREATE TABLE `OwbMeetingHandler` (
    `mid` VARCHAR(255) NOT NULL,
    `mhbtime` TIMESTAMP,
    `uhbtime` TIMESTAMP,
    `phbtime` TIMESTAMP,
    `mport`  INT(11) NOT NULL,
    `uport`  INT(11) NOT NULL,
    `pport`  INT(11) NOT NULL,
    PRIMARY KEY(`mid`)
)ENGINE = INNODB, DEFAULT CHARSET = UTF8;

CREATE TABLE `OwbMeetingRunTime` (
    `mid` VARCHAR(255) NOT NULL,
    `uname` VARCHAR(255) NOT NULL,
    `status` INT(11) NOT NULL DEFAULT 0,
    `hbtime` TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    PRIMARY KEY(`mid`, `uname`)
)ENGINE = INNODB, DEFAULT CHARSET = UTF8;

CREATE TABLE `OwbOperationsPool` (
    `mid` VARCHAR(255) NOT NULL,
    `opid` INT(11) NOT NULL,
    `value` BLOB NOT NULL,
    PRIMARY KEY(`mid`, `opid`)
)ENGINE = INNODB, DEFAULT CHARSET = UTF8;
