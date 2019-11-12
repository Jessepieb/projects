import os
import sys
import flask

import data.db_session as db_session

folder = os.path.abspath(os.path.join(os.path.dirname(__file__), '..'))
sys.path.insert(0, folder)


def register_all_blueprints():
    from views import home_views, planner_views, account_views, cms_views
    app.register_blueprint(home_views.homepage)
    app.register_blueprint(planner_views.planner)
    app.register_blueprint(account_views.account)
    app.register_blueprint(cms_views.cms)


def setup_db():
    db_file = os.path.join(os.path.dirname(__file__),
                           'db',
                           'planner.sqlite')
    db_session.global_init(db_file)


app = flask.Flask(__name__)
setup_db()
register_all_blueprints()


def main():
    app.run(debug=True)


if __name__ == '__main__':
    main()
