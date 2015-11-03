local MutableBuffer = require"MutableBuffer"

local Buf = MutableBuffer.New()

local String = "Hello"

Buf:Write(String,1)

print(Buf:Read(),Buf:Size(),Buf:Capacity())

Buf:Write("ap",2)

print(Buf:Read(),Buf:Size(),Buf:Capacity())

Buf:Write("py birthday",4)

print(Buf:Read(),Buf:Size(),Buf:Capacity())

Buf:Write"!"

print(Buf:Read(),Buf:Size(),Buf:Capacity())
