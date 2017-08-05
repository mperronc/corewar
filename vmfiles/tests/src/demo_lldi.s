.name "demo lldi"
.comment ""

ld %42, r2
st r2, -11
ld %4096, r5
lldi %-23, r5 , r4
