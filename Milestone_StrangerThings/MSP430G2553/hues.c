//working on separating this constant from the main code file
//Change these hexadecimal bytes to change colors.
//flag, blue, green, red. first few begin as red, ff = 255 = 11111111
static const byte huebytes[NHUEBYTES] = {
        0xfcu, 0x0u, 0x0u, 0xffu,
        0xfcu, 0x0u, 0xbu, 0xffu,
        0xfcu, 0x0u, 0x17u, 0xffu,
        0xfcu, 0x0u, 0x23u, 0xffu,
        0xfcu, 0x0u, 0x2fu, 0xffu,
        0xfcu, 0x0u, 0x3bu, 0xffu,
        0xf8u, 0x0u, 0x47u, 0xffu,
        0xf8u, 0x0u, 0x53u, 0xffu,
        0xf8u, 0x0u, 0x5fu, 0xffu,
        0xf8u, 0x0u, 0x6bu, 0xffu,
        0xf8u, 0x0u, 0x77u, 0xffu,
        0xf4u, 0x0u, 0x83u, 0xffu,
        0xf4u, 0x0u, 0x8fu, 0xffu,
        0xf4u, 0x0u, 0x9bu, 0xffu,
        0xf4u, 0x0u, 0xa7u, 0xffu,
        0xf4u, 0x0u, 0xb3u, 0xffu,
        0xf4u, 0x0u, 0xbfu, 0xffu,
        0xf0u, 0x0u, 0xcbu, 0xffu,
        0xf0u, 0x0u, 0xd7u, 0xffu,
        0xf0u, 0x0u, 0xe3u, 0xffu,
        0xf0u, 0x0u, 0xefu, 0xffu,
        0xf0u, 0x0u, 0xfbu, 0xffu,
        0xf0u, 0x0u, 0xffu, 0xf7u,
        0xf0u, 0x0u, 0xffu, 0xebu,
        0xf0u, 0x0u, 0xffu, 0xdfu,
        0xf0u, 0x0u, 0xffu, 0xd3u,
        0xf0u, 0x0u, 0xffu, 0xc7u,
        0xf1u, 0x0u, 0xffu, 0xbbu,
        0xf1u, 0x0u, 0xffu, 0xafu,
        0xf1u, 0x0u, 0xffu, 0xa3u,
        0xf1u, 0x0u, 0xffu, 0x97u,
        0xf1u, 0x0u, 0xffu, 0x8bu,
        0xf2u, 0x0u, 0xffu, 0x7fu,
        0xf2u, 0x0u, 0xffu, 0x73u,
        0xf2u, 0x0u, 0xffu, 0x67u,
        0xf2u, 0x0u, 0xffu, 0x5bu,
        0xf2u, 0x0u, 0xffu, 0x4fu,
        0xf2u, 0x0u, 0xffu, 0x43u,
        0xf3u, 0x0u, 0xffu, 0x37u,
        0xf3u, 0x0u, 0xffu, 0x2bu,
        0xf3u, 0x0u, 0xffu, 0x1fu,
        0xf3u, 0x0u, 0xffu, 0x13u,
        0xf3u, 0x0u, 0xffu, 0x7u,
        0xf3u, 0x3u, 0xffu, 0x0u,
        0xf3u, 0xfu, 0xffu, 0x0u,
        0xf3u, 0x1bu, 0xffu, 0x0u,
        0xf3u, 0x27u, 0xffu, 0x0u,
        0xf3u, 0x33u, 0xffu, 0x0u,
        0xf3u, 0x3fu, 0xffu, 0x0u,
        0xe3u, 0x4bu, 0xffu, 0x0u,
        0xe3u, 0x57u, 0xffu, 0x0u,
        0xe3u, 0x63u, 0xffu, 0x0u,
        0xe3u, 0x6fu, 0xffu, 0x0u,
        0xe3u, 0x7bu, 0xffu, 0x0u,
        0xd3u, 0x87u, 0xffu, 0x0u,
        0xd3u, 0x93u, 0xffu, 0x0u,
        0xd3u, 0x9fu, 0xffu, 0x0u,
        0xd3u, 0xabu, 0xffu, 0x0u,
        0xd3u, 0xb7u, 0xffu, 0x0u,
        0xc3u, 0xc3u, 0xffu, 0x0u,
        0xc3u, 0xcfu, 0xffu, 0x0u,
        0xc3u, 0xdbu, 0xffu, 0x0u,
        0xc3u, 0xe7u, 0xffu, 0x0u,
        0xc3u, 0xf3u, 0xffu, 0x0u,
        0xc3u, 0xffu, 0xffu, 0x0u,
        0xc3u, 0xffu, 0xf3u, 0x0u,
        0xc3u, 0xffu, 0xe7u, 0x0u,
        0xc3u, 0xffu, 0xdbu, 0x0u,
        0xc3u, 0xffu, 0xcfu, 0x0u,
        0xc3u, 0xffu, 0xc3u, 0x0u,
        0xc7u, 0xffu, 0xb7u, 0x0u,
        0xc7u, 0xffu, 0xabu, 0x0u,
        0xc7u, 0xffu, 0x9fu, 0x0u,
        0xc7u, 0xffu, 0x93u, 0x0u,
        0xc7u, 0xffu, 0x87u, 0x0u,
        0xcbu, 0xffu, 0x7bu, 0x0u,
        0xcbu, 0xffu, 0x6fu, 0x0u,
        0xcbu, 0xffu, 0x63u, 0x0u,
        0xcbu, 0xffu, 0x57u, 0x0u,
        0xcbu, 0xffu, 0x4bu, 0x0u,
        0xcfu, 0xffu, 0x3fu, 0x0u,
        0xcfu, 0xffu, 0x33u, 0x0u,
        0xcfu, 0xffu, 0x27u, 0x0u,
        0xcfu, 0xffu, 0x1bu, 0x0u,
        0xcfu, 0xffu, 0xfu, 0x0u,
        0xcfu, 0xffu, 0x3u, 0x0u,
        0xcfu, 0xffu, 0x0u, 0x7u,
        0xcfu, 0xffu, 0x0u, 0x13u,
        0xcfu, 0xffu, 0x0u, 0x1fu,
        0xcfu, 0xffu, 0x0u, 0x2bu,
        0xcfu, 0xffu, 0x0u, 0x37u,
        0xceu, 0xffu, 0x0u, 0x43u,
        0xceu, 0xffu, 0x0u, 0x4fu,
        0xceu, 0xffu, 0x0u, 0x5bu,
        0xceu, 0xffu, 0x0u, 0x67u,
        0xceu, 0xffu, 0x0u, 0x73u,
        0xceu, 0xffu, 0x0u, 0x7fu,
        0xcdu, 0xffu, 0x0u, 0x8bu,
        0xcdu, 0xffu, 0x0u, 0x97u,
        0xcdu, 0xffu, 0x0u, 0xa3u,
        0xcdu, 0xffu, 0x0u, 0xafu,
        0xcdu, 0xffu, 0x0u, 0xbbu,
        0xccu, 0xffu, 0x0u, 0xc7u,
        0xccu, 0xffu, 0x0u, 0xd3u,
        0xccu, 0xffu, 0x0u, 0xdfu,
        0xccu, 0xffu, 0x0u, 0xebu,
        0xccu, 0xffu, 0x0u, 0xf7u,
        0xccu, 0xfbu, 0x0u, 0xffu,
        0xccu, 0xefu, 0x0u, 0xffu,
        0xccu, 0xe3u, 0x0u, 0xffu,
        0xccu, 0xd7u, 0x0u, 0xffu,
        0xccu, 0xcbu, 0x0u, 0xffu,
        0xdcu, 0xbfu, 0x0u, 0xffu,
        0xdcu, 0xb3u, 0x0u, 0xffu,
        0xdcu, 0xa7u, 0x0u, 0xffu,
        0xdcu, 0x9bu, 0x0u, 0xffu,
        0xdcu, 0x8fu, 0x0u, 0xffu,
        0xdcu, 0x83u, 0x0u, 0xffu,
        0xecu, 0x77u, 0x0u, 0xffu,
        0xecu, 0x6bu, 0x0u, 0xffu,
        0xecu, 0x5fu, 0x0u, 0xffu,
        0xecu, 0x53u, 0x0u, 0xffu,
        0xecu, 0x47u, 0x0u, 0xffu,
        0xfcu, 0x3bu, 0x0u, 0xffu,
        0xfcu, 0x2fu, 0x0u, 0xffu,
        0xfcu, 0x23u, 0x0u, 0xffu,
        0xfcu, 0x17u, 0x0u, 0xffu,
        0xfcu, 0xbu, 0x0u, 0xffu
};