-- created for SQLITE

-- should run : sqlite3 spi.db < install.sql
     
--    This file is part of Vigil.
--
--    Vigil is free software: you can redistribute it and/or modify it under the terms of the 
--    GNU General Public License as published by the Free Software Foundation, either version 3 
--    of the License, or (at your option) any later version.
--
--    Vigil is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
--    without  even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
--    See the GNU General Public License for more details.
--
--    You should have received a copy of the GNU General Public License along with Vigil. 
--    If not, see <https://www.gnu.org/licenses/>. 


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