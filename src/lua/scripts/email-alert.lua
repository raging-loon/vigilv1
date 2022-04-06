-- 
-- Copyright 2021-2022 Conner Macolley
-- 
--    Licensed under the Apache License, Version 2.0 (the "License");
--    you may not use this file except in compliance with the License.
--    You may obtain a copy of the License at
-- 
--        http://www.apache.org/licenses/LICENSE-2.0
-- 
--    Unless required by applicable law or agreed to in writing, software
--    distributed under the License is distributed on an "AS IS" BASIS,
--    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
--    See the License for the specific language governing permissions and
--    limitations under the License.
-- 

-- this script includes everything to send an email about a rule alert

-- email pushed as an argument



local function main()
  -- local maillist = io.open("/etc/vigil/maillist","r")
  
  local port = nil
  local password = ""
  local rcpt = ""
  local sender = ""
  local server = ""

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
        server = values[2]
      elseif(values[1] == "port") then
        port = values[2]
      elseif(values[1] == "rcpt") then
        rcpt = values[2]
      elseif(values[1] == "sender") then
        sender = values[2]
      elseif(values[1] == "pass") then
        password = values[2]
      end

    
    end    
    
    --
  end 
  -- maillist:close();
end

main()
