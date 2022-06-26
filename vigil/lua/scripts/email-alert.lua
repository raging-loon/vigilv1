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

-- Modified version of the script writting by Michal Kottman

-- this script includes everything to send an email about a rule alert

-- email pushed as an argument

local socket = require("socket")
local smtp = require("socket.smtp")
local ssl = require("ssl")
local https = require("ssl.https")
local ltn12 = require("ltn12")


function sslCreate()
  local sock = socket.tcp()
  return setmetatable({
    connect = function(_, host, port)
      local r, e = sock:connect(host,port)
      if not r then return r, e end
      sock = ssl.wrap(sock, {mode="client",protocol='sslv23'})
      return sock:dohandshake()
    end
  }, {
    __index = function(t,n)
      return function(_,...)
        return sock[n](sock,...)
      end
    end
  })
end


local function main()
  -- local maillist = io.open("/etc/vigil/maillist","r")
  
  local port = nil
  local pass = ""
  local rcpt = ""
  local sender = ""
  local serv = ""

  local lines = {}
  for line in io.lines("/etc/vigil/maillist") do
    lines[#lines + 1] = line
  end

  for i,v in pairs(lines) do
    if(string.sub(v,1,1) ~= "#") then
      values = {}
      for s in v:gmatch("[^:]+") do
        table.insert(values,s)
      end

      if(values[1] == "server") then
        serv = values[2]
      elseif(values[1] == "port") then
        port = values[2]
      elseif(values[1] == "rcpt") then
        rcpt = values[2]
      elseif(values[1] == "sender") then
        sender = values[2]
      elseif(values[1] == "pass") then
        pass = values[2]
      end

    
    end    
    
    --
  end
  local msg = {
    headers = {
      from = sender,
      to = rcpt,
      subject = "VIGIL IDS Alert"
    },
    body = "The IDS Has picked up an error"
  } 

  local ok, err = smtp.send {
    from = sender,
    to = rcpt,
    source = smtp.message(msg),
    username = sender,
    password = pass,
    server = serv,
    port = tonumber(port),
    create = sslCreate
  }
  if not ok then
    print("Message failed to send", err)
  end
  -- maillist:close();
end

main()
