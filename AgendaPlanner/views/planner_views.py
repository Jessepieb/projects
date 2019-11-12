import flask
from infrastructure.view_modifiers import  response

planner = flask.Blueprint('planner', __name__, url_prefix='/planner')


@planner.route('/')
@response(template_file='planner/calender.html')
def calender():
    return {}