<?php

class spi_members{
	public string $serv_addr;
	public string $cli_addr;
	public int $serv_port;
	public int $cli_port;
	public int $serv_packet_sent;
	public int $cli_packet_sent;
	public int $serv_packet_recv;
	public int $cli_packet_recv;
	public int $protocol;
	public int $pps;
	public int $start_time;
	public int $end_time;
	public int $control_pkt;
	public int $data_pkt;
}

?>