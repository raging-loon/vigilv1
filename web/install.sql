-- created for MYSQL

CREATE USER 'NPSI'@'localhost' IDENTIFIED BY 'temppassword';
GRANT ALL PRIVILEGES ON * . * TO 'NPSI'@'localhost';
FLUSH PRIVILEGES;

CREATE DATABASE NPSIDB;
USE NPSIDB DATABASE;

CREATE TABLE watchlist (
  ip_address varchar(20),
  danger_level int
);

CREATE TABLE arp_cache (
  ip_address varchar(20),
  mac_address varchar(25)
);