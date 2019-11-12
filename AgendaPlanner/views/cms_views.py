import flask

from infrastructure.view_modifiers import  response
import services.cms_service as cms_service

cms = flask.Blueprint('cms', __name__)


@cms.route('/<path:full_url>')
@response(template_file='services/cms.html')
def cms_page(full_url: str):

    print(f'Getting CMS page for {full_url}')
    page = cms_service.get_page(full_url)
    if not page:
        return flask.abort(404)
    print(page)
    return page
