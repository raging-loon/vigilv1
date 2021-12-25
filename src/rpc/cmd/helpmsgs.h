#ifndef HELPMSGS_H
#define HELPMSGS_H


const char * get_cmd_help = 
        "Help for \"get\" command:\n"
        "\tblacklist -> retrieve the blacklist\n"
        "\trules -> retrieve rules loaded in memory\n"
        "\tmatches -> retrieve matches for all rules\r\n";

const char * add_cmd_help =
        "Help for \"add\" command:\n"
        "\tadd blacklist <ipv4|ipv6> <ip addr>\r\n";

#endif /* HELPMSGS_H */