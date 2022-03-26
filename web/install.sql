-- created for SQLITE

-- CREATE USER 'VIGIL'@'localhost' IDENTIFIED BY 'Pa@@w0rD';
-- GRANT ALL PRIVILEGES ON * . * TO 'VIGIL'@'localhost';
-- FLUSH PRIVILEGES;

CREATE DATABASE VIGIL;
USE VIGIL DATABASE;

CREATE TABLE watchlist (
  ip_address varchar(20),
  danger_level int
);

CREATE TABLE arp_cache (
  ip_address varchar(20),
  mac_address varchar(25)
);

CREATE TABLE ip_stats(
  ip_address varchar(20),
  total_pkts int,
  total_sent int,
  total_recv int,
  tcp_sent int,
  tcp_recv int,
  udp_sent int,
  udp_recv int,
  icmp_sent int,
  icmp_recv int
);