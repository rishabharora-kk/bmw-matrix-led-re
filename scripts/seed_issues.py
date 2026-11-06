#!/usr/bin/env python3
"""Explicit opt-in issue seeder, requires authorized GitHub CLI; idempotent by issue ID.

This is NOT run automatically by CI or by any offline demo.
"""
import json
import re
import subprocess
import sys
from pathlib import Path


def gh(*args: str) -> str:
    return subprocess.check_output(['gh', *args], text=True).strip()


def main() -> None:
    if len(sys.argv) != 2 or '/' not in sys.argv[1]:
        raise SystemExit('Usage: seed_issues.py owner/repo')
    repo = sys.argv[1]
    rows = []
    for line in Path(__file__).resolve().parents[1].joinpath('ROADMAP.md').read_text().splitlines():
        if not re.match(r'^\| BMW-\d{3} \|', line):
            continue
        cells = [c.strip() for c in line.strip('|').split('|')]
        rows.append(cells)
    # Real GitHub milestone objects; not just ROADMAP labels.
    found = json.loads(gh('api', f'repos/{repo}/milestones?state=all&per_page=100'))
    known_milestones = {item['title'] for item in found}
    for _, milestone, _, _, _ in rows:
        if milestone not in known_milestones:
            gh('api', '-X', 'POST', f'repos/{repo}/milestones', '-f', f'title={milestone}',
               '-f', 'description=Bench-only research gate; see ROADMAP.md')
            known_milestones.add(milestone)
            print('MILESTONE', milestone)
    existing = json.loads(gh('issue', 'list', '-R', repo, '--state', 'all', '--limit', '200', '--json', 'title'))
    titles = {item['title'] for item in existing}
    for number, milestone, priority, deliverable, exit_criterion in rows:
        title = f'{number}: {deliverable}'
        if title in titles:
            print('SKIP', title)
            continue
        body = (f'### Milestone\n{milestone}\n\n### Priority\n{priority}\n\n'
                f'### Exit criterion\n{exit_criterion}\n\n'
                '### Guardrails\nOwned bench hardware only. Do not submit proprietary files, VINs, '
                'security material, guessed pinouts or road-use modifications. '
                'Provide evidence grade and source link.\n\n'
                'See [ROADMAP.md](ROADMAP.md) and [research/sources.md](research/sources.md).')
        gh('issue', 'create', '-R', repo, '--milestone', milestone, '--title', title, '--body', body)
        print('CREATED', title)


if __name__ == '__main__':
    main()
