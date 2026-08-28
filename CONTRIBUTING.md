# Contributing

AratMicro is an open-source micromouse project built for Robosam and MEB Robot. We welcome bug reports, documentation improvements, and hardware and software contributions.

## How to contribute

1. Fork the repository or create a branch.
2. Keep changes focused and small — avoid mixing unrelated topics in a single PR.
3. Write clear commit messages in English.
4. Open a pull request with a brief summary of what changed and why.

## Development setup

### Software

```bash
cd software
pio run -e aratmicro_f411    # build
pio test -e native           # unit tests
pio check -e aratmicro_f411  # clang-tidy (optional)
```

Code style: follow existing C++17 patterns. Pay attention to `-Wall -Wextra -Wpedantic` warnings.

### Hardware (KiCad)

- Use KiCad **10.x**.
- Project file: `hardware/pcb/AratMicro.kicad_pro`
- Do not commit `.history/` or `*-backups/` folders (excluded in `.gitignore`).
- When editing schematics, update the relevant sub-sheet (`mcu.kicad_sch`, `mc.kicad_sch`, etc.).

## Commit conventions

- `feat:` new feature
- `fix:` bug fix
- `docs:` documentation only
- `hardware:` PCB / schematic change
- `refactor:` code change without behavior change

Example: `feat: add DRV8833 PWM motor driver module`

## Pull request checklist

- [ ] Build completes without errors (`pio run`)
- [ ] Tests pass, if applicable (`pio test -e native`)
- [ ] Hardware changes update `hardware/README.md` or `software/docs/hardware.md`
- [ ] No secrets, personal paths, or `.history/` files added

## Code of conduct

Be respectful and constructive. Technical criticism is not personal — we are building a better robot together.

## Questions

Open an issue to discuss design decisions. For large architectural changes, start with an issue before opening a PR.
