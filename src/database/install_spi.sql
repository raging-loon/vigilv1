-- created for SQLITE

-- should run : sqlite3 spi.db < install.sql

CREATE TABLE spi_table(
  serv_addr varchar(24),
  cli_addr varchar(24),
  serv_port int,
  cli_port int,
  serv_pkt_sent int,
  cli_pkt_sent int,
  serv_pkt_recv int,
  cli_pkt_recv int,
  protocol int,
  avg_pps int,
  start_time int,
  end_time int,
  data_pkts int,
  control_pkts int
);