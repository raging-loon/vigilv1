# NPSI Rule Documentation

This is the official documentation for the rules in the NPSI program

## Format

The basic format of a rule is as follows:

alert stdout \<port\> \<protocol\> (\<arguments\>)

For example:
```snort
alert stdout 23 TCP (name:"invalid-login"; msg:"INFO Invalid login"; type:str_match; target:"Invalid login";)
```
This would create a rule called 'invalid-login' that displayed the message 'INFO Invalid login' when ever it fins the string "Invalid login" in a packet with TCP port 23;

## name:
The name parameter is simply the name of the rule for management, debuggin, and organizational purposes.

It must not have any whitespaces or non-ascii characters. Support for unicode characters may come in the future.

The name must also not be longer than 24 characters.

## msg:

This is the string that will be present on the screen and in the log file. It may have white spaces(one white space to seperate words);

The message cannot exceed 128 characters in length.

## type:

This determines how the packet will be processed. 

Supported types\:
<ol>
<li>str_match -> Match raw bytes. ASCII characters will be converted to bytes</li>
<li>pcre -> match regular expressions</li>
<li>none -> do not look for anything.</li>
</ol>

## target:
The target for str_match. Must use | | for raw bytes, for example:<br>
|9090909090| would match 5 bytes equal to 0x90
Note that these bytes <b>MUST BE LOWERCASE</b> 
## pcre:
The same as target, but uses regex instead of substrings.

# Protocol Specific Data

<table>
  <tr>
    <th>Keyword</th>
    <th>Function</th>
  </tr>
  <tr>
    <td>ttl</td>
    <td>matches the ttl in the ipv4 or ipv6 header
  </tr>
  <tr>
    <td>itype</td>
    <td>matches the ICMP type</td>
  </tr>
    <tr>
    <td>icode</td>
    <td>Matches the ICMP code</td>
  </tr>
    <tr>
    <td>dsize</td>
    <td>Matches destination size(note, operators such as > are acceptable)</td>
  </tr>
</table>