fake_db = {
    '/test/jesse':{
        'account_name': 'Jesse',
        'age': '22',
    },
    '/test/welmoed':{
        'account_name': 'Welmoed',
        'age': '20',
    },
}


def get_page(url: str) -> dict:
    if not url:
        return {}

    url = url.strip().lower()
    url = '/' + url.lstrip('/')
    page = fake_db.get(url, {})
    return page
