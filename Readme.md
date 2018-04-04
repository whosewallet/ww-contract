# Setup whosewallet master account
1. Create key

```bash
cleos create key && cleos create key

Private key: 5Hr5nXogAsggpYzRfLXFXFyE4t4YfY29PhZzfgh7LoG3V9zBUsn
Public key: EOS6Uab5iaypSdc2dRAkvsFx1SD5s4U9zzG2c4PViiVZDzwuLTKeE

Private key: 5Kb4JsT35UtLBZ3G2WzALVP9LYrgTzoZg48igSN2dmKwxxGEBPN
Public key: EOS6f39NisBEiFpMCZ4LaBHmtCUQ8wKcccLAY1rzSE2R7ZNHTS4C2
```

2. Create account

```bash
$ cleos create account eosio whosewallet EOS6Uab5iaypSdc2dRAkvsFx1SD5s4U9zzG2c4PViiVZDzwuLTKeE EOS6f39NisBEiFpMCZ4LaBHmtCUQ8wKcccLAY1rzSE2R7ZNHTS4C2

executed transaction: bd65b116a76c415b32fab8114398f86b07038000977752c6a78a20fb86be8f8a  364 bytes  1000 cycles
#         eosio <= eosio::newaccount            "0000000000ea305500b28ad1708569e301000000010002d11a291731c406e5fc5ee617353e97ce7e152d5b0d5d31ed21b4e...

```
__NOTE:__ _Remember to replace owner key and active key with your own_

# Build & deploy

```bash
$ ./build.sh

5 warnings generated.
main.wast

$ ./deploy.sh
````

# Pre-define

- Bitcoin address type: 50
- Ethereum address type: 100

# Sample

#### set a wallet for user
1. Create account: `acmv` and `haiz`

```bash
$ cleos create account whosewallet acmv EOS6Uab5iaypSdc2dRAkvsFx1SD5s4U9zzG2c4PViiVZDzwuLTKeE EOS6f39NisBEiFpMCZ4LaBHmtCUQ8wKcccLAY1rzSE2R7ZNHTS4C2

$ cleos create account whosewallet haiz EOS6Uab5iaypSdc2dRAkvsFx1SD5s4U9zzG2c4PViiVZDzwuLTKeE EOS6f39NisBEiFpMCZ4LaBHmtCUQ8wKcccLAY1rzSE2R7ZNHTS4C2

executed transaction: 88a47cfbae49d737b2f7b440f4cd5dce25b36f060a770ef30ed4ef2ef7aa5ec8  364 bytes  1000 cycles
#         eosio <= eosio::newaccount            "00b28ad1708569e30000000000b0253201000000010002d11a291731c406e5fc5ee617353e97ce7e152d5b0d5d31ed21b4e...

executed transaction: f63a444bc2b9c7921ad76021414b0ad2b786249d6aabd4a2b3758be1365b4d45  364 bytes  1000 cycles
#         eosio <= eosio::newaccount            "00b28ad1708569e30000000000f09d6901000000010002d11a291731c406e5fc5ee617353e97ce7e152d5b0d5d31ed21b4e...
```

2. User `acmv` want to save his wallet address info `0x1a4C8627eeCf38d7392B7637123a899ff559f0A0`. This is an Ethereum address, so the type must be `100`.

```bash
cleos push action whosewallet inrnw '{ "w_add": "0x1a4C8627eeCf38d7392B7637123a899ff559f0A0", "w_type": "100", "a_name": "acmv" }' -p whosewallet@active -p acmv@active
```

3. User `haiz` want to save his wallet address info `12N22uVNofBYaNfjCSdzpVPcyd5Lfh11zq`. This is an Bitcoin address, so the type must be `50`.

```bash
cleos push action whosewallet inrnw '{ "w_add": "12N22uVNofBYaNfjCSdzpVPcyd5Lfh11zq", "w_type": "50", "a_name": "haiz" }' -p whosewallet@active -p haiz@active
```

4. Verify:

```bash
$ cleos get table whosewallet acmv mywallet

{
  "rows": [{
      "id": "3305419447951227220",
      "w_type": 100,
      "w_add": "0x1a4C8627eeCf38d7392B7637123a899ff559f0A0"
    }
  ],
  "more": false
}

$ cleos get table whosewallet haiz mywallet

{
  "rows": [{
      "id": "4124316577211100456",
      "w_type": 50,
      "w_add": "12N22uVNofBYaNfjCSdzpVPcyd5Lfh11zq"
    }
  ],
  "more": false
}

$ cleos get table whosewallet whosewallet alwallet                                                                      

{
  "rows": [{
      "id": "3305419447951227220",
      "a_name": "acmv"
    },{
      "id": "4124316577211100456",
      "a_name": "haiz"
    }
  ],
  "more": false
}

```

# Search user name by wallet id
Suppose that we have wallet address `12N22uVNofBYaNfjCSdzpVPcyd5Lfh11zq` and we want to know whose it is belong to.

1. Calculate hash of `12N22uVNofBYaNfjCSdzpVPcyd5Lfh11zq` to get id `4124316577211100456`
2. Use command below

```bash
cleos get table whosewallet whosewallet alwallet -l 1 -L 4124316577211100456

{
  "rows": [{
      "id": "4124316577211100456",
      "a_name": "haiz"
    }
  ],
  "more": true
}
```