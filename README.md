# lily58-keymap
My Lily58 Keymaps &amp; Configuration

1. Go to qmk_firmware folder
2. Make a new keymap
3. Clone into new keymap folder
4. Compile for desired microprocessor
5. Done!

```bash
cd keyboards/lily58/keymaps/
```

```bash
mkdir zukuo
```

```bash
git clone git@github.com:zukuo/lily58-keymap.git
```

```bash
sudo qmk compile -c -kb lily58 -km zukuo -e CONVERT_TO=promicro_rp2040
```
